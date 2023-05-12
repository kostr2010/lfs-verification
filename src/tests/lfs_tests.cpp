#include <array>
#include <cassert>
#include <thread>

#include "lfs.h"

#include "gtest/gtest.h"

LFS stack{ "trace.log" };

static constexpr int N_THREADS = 500;
static constexpr int TASK_SIZE = 500;

static void PushPopTask()
{
    for (int i = 0; i < TASK_SIZE; ++i) {
        stack.Push(i);
        stack.Pop();
    }
}

static void PushTask()
{
    for (int i = 0; i < TASK_SIZE; ++i) {
        stack.Push(i);
    }
}

static void PopTask()
{
    for (int i = 0; i < TASK_SIZE; ++i) {
        stack.Pop();
    }
}

TEST(TestsLFS, TestPushPop)
{
    std::array<std::thread, N_THREADS> threads;

    for (auto i = 0U; i < threads.size(); ++i) {
        threads[i] = std::thread(PushPopTask);
    }

    for (auto i = 0U; i < threads.size(); ++i) {
        threads[i].join();
    }

    assert(stack.Empty());
}

TEST(TestsLFS, TestPopAfterPush)
{
    std::array<std::thread, N_THREADS> threads;

    for (auto i = 0U; i < threads.size(); ++i) {
        threads[i] = std::thread(PushTask);
    }

    for (auto i = 0U; i < threads.size(); ++i) {
        threads[i].join();
    }

    for (auto i = 0U; i < threads.size(); ++i) {
        threads[i] = std::thread(PopTask);
    }

    for (auto i = 0U; i < threads.size(); ++i) {
        threads[i].join();
    }

    assert(stack.Empty());
}

TEST(TestsLFS, TestMixed)
{
    std::array<std::thread, 100> threads;
    for (auto i = 0U; i < threads.size() / 2; ++i) {
        threads[i] = std::thread(PushTask);
    }

    for (auto i = threads.size() / 2; i < threads.size(); ++i) {
        threads[i] = std::thread(PopTask);
    }

    for (auto i = 0U; i < threads.size(); ++i) {
        threads[i].join();
    }
}
