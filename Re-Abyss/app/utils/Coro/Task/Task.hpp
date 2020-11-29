#pragma once
#include <coroutine>
#include <optional>

namespace abyss::Coro
{
    struct TaskPromice;

    struct Task
    {
        friend struct TaskPromice;
        using promise_type = TaskPromice;
        using handle = std::coroutine_handle<promise_type>;

        Task(Task const&) = delete;
        Task(Task&& rhs) noexcept
            : m_coro(rhs.m_coro)
        {
            rhs.m_coro = nullptr;
        }
        ~Task()
        {
            if (m_coro) {
                m_coro.destroy();
            }
        }
        Task(handle h) :
            m_coro(h)
        {}

        bool moveNext() const;
        [[nodiscard]] bool isDone() const;
    private:
        handle m_coro;
    };

    struct TaskPromice
    {
        static auto get_return_object_on_allocation_failure() { return Task{ nullptr }; }
        auto get_return_object() { return Task{ Task::handle::from_promise(*this) }; }
        auto initial_suspend() { return std::suspend_always{}; }
        auto final_suspend() noexcept { return std::suspend_always{}; }
        void unhandled_exception() { std::terminate(); }
        void return_void() {}

        auto yield_value(int)
        {
            return std::suspend_always{};
        }

        auto yield_value(Task&& other)
        {
            next.emplace(std::move(other));

            auto nextCoro = next->m_coro;
            if (!nextCoro.done()) {
                nextCoro.resume();
            }
            auto ready = nextCoro.done();
            struct awaiter
            {
                bool ready = false;
                awaiter(bool r) :
                    ready(r)
                {}
                bool await_ready() const{ return ready; }
                void await_resume()
                {}
                void await_suspend(std::coroutine_handle<>)
                {}
            };
            return awaiter{ ready };
        }

        std::optional<Task> next;
    };

    [[nodiscard]] Task operator & (Task a, Task b);

    [[nodiscard]] Task operator | (Task a, Task b);

    [[nodiscard]] Task operator + (Task a, Task b);
}