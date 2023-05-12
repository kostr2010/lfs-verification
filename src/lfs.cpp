#include "lfs.h"

#include <cassert>
#include <cstdio>

LFS::LFS(const std::string& fname)
{
    log_ = fopen(fname.c_str(), "w");
    assert(log_ != nullptr);
}

LFS::~LFS()
{
    assert(log_ != nullptr);
    assert(fclose(log_) == 0);
}

void LFS::Push(data_t const& data)
{
    Log(Op::PUSH);

    Node* const new_node = new Node(data);
    new_node->next_ = head_.load();

    WAIT(head_.compare_exchange_weak(new_node->next_, new_node));
}

std::shared_ptr<data_t> LFS::Pop()
{
    Log(Op::POP);

    ++pop_queue_size_;
    Node* old_head = head_.load();

    WAIT(head_.compare_exchange_weak(old_head, old_head->next_) || old_head == nullptr);

    std::shared_ptr<data_t> res{};
    if (old_head) {
        res.swap(old_head->data_);
    }
    Collect(old_head);

    return res;
}

bool LFS::Empty()
{
    return head_ == nullptr;
}

void LFS::Log(Op op)
{
    assert(log_ != nullptr);

    switch (op) {
    case Op::PUSH:
        fwrite("0", 1, 1, log_);
        break;
    case Op::POP:
        fwrite("1", 1, 1, log_);
        break;
    default:
        UNREACHABLE("unhandled stack operation");
    }
}

void LFS::Free(Node* nodes)
{
    while (nodes) {
        Node* next = nodes->next_;
        delete nodes;
        nodes = next;
    }
}

void LFS::Collect(Node* old_head)
{
    if (pop_queue_size_ == 1) {
        Node* nodes_to_delete = collect_queue_.exchange(nullptr);
        if (!--pop_queue_size_) {
            Free(nodes_to_delete);
        } else if (nodes_to_delete) {
            ChainPending(nodes_to_delete);
        }
        delete old_head;
    } else {
        ChainPending(old_head, old_head);
        --pop_queue_size_;
    }
}

void LFS::ChainPending(Node* nodes)
{
    Node* last = nodes;
    while (Node* const next = last->next_) {
        last = next;
    }
    ChainPending(nodes, last);
}

void LFS::ChainPending(Node* first, Node* last)
{
    last->next_ = collect_queue_;
    WAIT(collect_queue_.compare_exchange_weak(last->next_, first));
}
