#pragma once
#include <coroutine>
#include <memory>

namespace abyss::Coro
{
    namespace detail
    {
        struct Yield
        {
            constexpr Yield():
                count(1)
            {}

            constexpr Yield(std::uint32_t _count) :
                count(_count)
            {}

            std::uint32_t count;
        };

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
        struct promise_type; // coroutine_traitsを特殊化してないのでスネイクケース
        using Handle = std::coroutine_handle<promise_type>;

        struct PromiseValue
        {
            void return_value(const T& value)
            {
                this->value = value;
            }

            const T& getValue() const
            {
                return value;
            }
            T value;
        };


        struct promise_type : PromiseValue
        {
            static Task get_return_object_on_allocation_failure()
            {
                return Task{ nullptr };
            }
            auto get_return_object() { return Task{ Task::Handle::from_promise(*this) }; }
            auto initial_suspend() { return std::suspend_never{}; }
            auto final_suspend() noexcept { return std::suspend_always{}; }
            void unhandled_exception() { std::terminate(); }

            auto yield_value(const detail::Yield& _yield)
            {
                struct Awaiter
                {
                    bool await_ready() const noexcept
                    {
                        return ready;
                    }

                    void await_suspend(std::coroutine_handle<>){}
                    void await_resume(){}

                    bool ready = false;
                };
                if (_yield.count == 0) {
                    return Awaiter{true};
                }
                --(this->yield = _yield).count;
                return Awaiter{false};
            }
            template<class U>
            auto yield_value(Task<U> other)
            {
                auto nextTask = std::make_shared<Task<U>>(std::move(other));
                auto ready = !nextTask->moveNext();
                next = nextTask;
                struct Awaiter
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
                return Awaiter{ ready, nextTask };
            }
            detail::Yield yield;
            std::shared_ptr<detail::ITask> next;
        };

        Task(Handle h) :
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
            // Yield
            {
                auto& yield = coro.promise().yield;
                if (yield.count > 0 && yield.count-- > 0) {
                    // カウンタが残ってるなら
                    return true;
                }
            }
            // 割り込み別タスク
            {
                auto& next = coro.promise().next;
                if (next) {

                    if (!next->moveNext()) {
                        next = nullptr;
                    } else {
                        return true;
                    }
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
        [[nodiscard]] decltype(auto) get() const
        {
            return coro.promise().getValue();
        }

    private:
        Handle coro;
    };

    // void特殊化
    template<>
    struct Task<void>::PromiseValue
    {
        void return_void() {}

        void getValue() const
        {}
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