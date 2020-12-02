#pragma once
#include <coroutine>
#include <memory>

namespace abyss::Coro
{
    namespace detail
    {
        /// <summary>
        /// タスク用インターフェース
        /// </summary>
        struct ITask
        {
            virtual ~ITask() = default;
            virtual bool moveNext() const = 0;
        };
    }

    /// <summary>
    /// タスク
    /// </summary>
    template <class T = void>
    struct Task : detail::ITask
    {
        struct promise_type;
        using handle = std::coroutine_handle<promise_type>;

        struct promise_type
        {
            static Task get_return_object_on_allocation_failure()
            {
                return Task{ nullptr };
            }
            auto get_return_object() { return Task{ Task::handle::from_promise(*this) }; }
            auto initial_suspend() { return std::suspend_always{}; }
            auto final_suspend() noexcept { return std::suspend_always{}; }
            void unhandled_exception() { std::terminate(); }
            void return_value(const T& value)
            {
                this->value = value;
            }

            auto yield_value(int)
            {
                return std::suspend_always{};
            }
            template<class U>
            auto yield_value(Task<U> other)
            {
                auto nextTask = std::make_shared<Task<U>>(std::move(other));
                auto ready = !nextTask->moveNext();
                next = nextTask;
                struct awaiter
                {
                    bool ready = false;
                    std::shared_ptr<Task<U>> pTask;

                    bool await_ready() const { return ready; }
                    decltype(auto) await_resume()
                    {
                        return pTask->get();
                    }
                    void await_suspend(std::coroutine_handle<>)
                    {}
                };
                return awaiter{ ready, nextTask };
            }
            std::shared_ptr<detail::ITask> next;

            T value;
        };

        Task(handle h) :
            coro(h)
        {}

        Task(Task const&) = delete;

        Task(Task&& rhs) noexcept
            : coro(std::move(rhs.coro))
        {
            rhs.coro = nullptr;
        }

        ~Task()
        {
            if (coro) {
                coro.destroy();
            }
        }

        /// <summary>
        /// 再開
        /// </summary>
        /// <returns></returns>
        bool moveNext() const override
        {
            if (!coro) {
                return false;
            }
            if (coro.done()) {
                return false;
            }
            auto& next = coro.promise().next;
            if (next) {

                if (!next->moveNext()) {
                    next = nullptr;
                } else {
                    return true;
                }
            }
            coro.resume();
            return !coro.done();
        }

        /// <summary>
        /// 完了したか
        /// </summary>
        /// <returns></returns>
        [[nodiscard]] bool isDone()const
        {
            if (!coro) {
                return false;
            }
            return coro.done();
        }

        /// <summary>
        /// 取得
        /// </summary>
        /// <returns></returns>
        [[nodiscard]] const T& get() const
        {
            return coro.promise().value;
        }

    private:
        handle coro;
    };

    /// <summary>
    /// タスク void特殊化
    /// </summary>
    template <>
    struct Task<void> : detail::ITask
    {
        struct promise_type;
        using handle = std::coroutine_handle<promise_type>;

        struct promise_type
        {
            static Task get_return_object_on_allocation_failure()
            {
                return Task{ nullptr };
            }
            auto get_return_object() { return Task{ Task::handle::from_promise(*this) }; }
            auto initial_suspend() { return std::suspend_always{}; }
            auto final_suspend() noexcept { return std::suspend_always{}; }
            void unhandled_exception() { std::terminate(); }
            void return_void() {}

            auto yield_value(int)
            {
                return std::suspend_always{};
            }
            template<class U>
            auto yield_value(Task<U> other)
            {
                auto nextTask = std::make_shared<Task<U>>(std::move(other));
                auto ready = !nextTask->moveNext();
                next = nextTask;
                struct awaiter
                {
                    bool ready = false;
                    std::shared_ptr<Task<U>> pTask;

                    bool await_ready() const { return ready; }
                    decltype(auto) await_resume()
                    {
                        return pTask->get();
                    }
                    void await_suspend(std::coroutine_handle<>)
                    {}
                };
                return awaiter{ ready, nextTask };
            }
            std::shared_ptr<detail::ITask> next;
        };

        Task(handle h) :
            coro(h)
        {}

        Task(Task const&) = delete;

        Task(Task&& rhs) noexcept
            : coro(std::move(rhs.coro))
        {
            rhs.coro = nullptr;
        }
        ~Task()
        {
            if (coro) {
                coro.destroy();
            }
        }

        /// <summary>
        /// 再開
        /// </summary>
        /// <returns></returns>
        bool moveNext() const override
        {
            if (!coro) {
                return false;
            }
            if (coro.done()) {
                return false;
            }
            auto& next = coro.promise().next;
            if (next) {

                if (!next->moveNext()) {
                    next = nullptr;
                } else {
                    return true;
                }
            }
            coro.resume();
            return !coro.done();
        }

        /// <summary>
        /// 完了したか
        /// </summary>
        /// <returns></returns>
        bool isDone()const
        {
            if (!coro) {
                return false;
            }
            return coro.done();
        }

        void get() const
        {}
    private:
        handle coro;
    };

    template<class T, class U>
    [[nodiscard]] Task<void> operator & (Task<T> a, Task<U> b)
    {
        while (true) {
            a.moveNext();
            b.moveNext();

            if (a.isDone() && b.isDone()) {
                co_return;
            }

            co_yield{};
        }
    }


    template<class T, class U>
    [[nodiscard]] Task<void> operator | (Task<T> a, Task<U> b)
    {
        while (true) {
            a.moveNext();
            b.moveNext();

            if (a.isDone() || b.isDone()) {
                co_return;
            }

            co_yield{};
        }
    }

    template<class T, class U>
    [[nodiscard]] Task<U> operator + (Task<T> a, Task<U> b)
    {
        while (a.moveNext()) {
            co_yield{};
        }
        while (b.moveNext()) {
            co_yield{};
        }
        co_return b.get();
    }
}