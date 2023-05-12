#ifndef __LFS_H_INCLUDED__
#define __LFS_H_INCLUDED__

#include <atomic>
#include <memory>
#include <string>

#include "macros.h"

// non-template for simplicity, as we only need to test the algorithm
using data_t = int;

class LFS
{
    enum class Op
    {
        PUSH,
        POP,
    };

    struct Node
    {
        Node(data_t const& data) : data_(std::make_shared<data_t>(data))
        {
        }

        std::shared_ptr<data_t> data_;
        Node* next_{ nullptr };
    };

  public:
    LFS(const std::string& fname);
    ~LFS();

    NO_COPY_SEMANTIC(LFS);
    NO_MOVE_SEMANTIC(LFS);

    void Push(data_t const& data);
    std::shared_ptr<data_t> Pop();

    bool Empty();

  private:
    void Log(Op op);

    void Collect(Node* old_head);
    void ChainPending(Node* nodes);
    void ChainPending(Node* first, Node* last);
    static void Free(Node* nodes);

    std::atomic<Node*> collect_queue_{ nullptr };
    std::atomic<unsigned> pop_queue_size_{ 0 };
    std::atomic<Node*> head_{ nullptr };

    FILE* log_{ nullptr };
};

#endif
