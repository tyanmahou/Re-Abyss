#pragma once
#include <coroutine>
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::Coro
{
    template<class Type>
    struct AsyncGenerator
    {
        struct promise_type;
        using handle = std::coroutine_handle<promise_type>;

        struct promise_type
        {
            Type value;
            auto get_return_object() { return AsyncGenerator{ handle::from_promise(*this) }; }
            auto  initial_suspend() { return std::suspend_always{}; }
            auto final_suspend() noexcept { return std::suspend_always{}; }
            auto yield_value(const Type& _value)
            {
                this->value = _value;
                isFindValue = true;
                return std::suspend_always{};
            }
            auto yield_value(const Yield& _yield)
            {
                return operator co_await(_yield);
            }
            void unhandled_exception() { std::terminate(); }
            void return_void() {}
            Yield yield{ 0 };
            detail::NextTaskHandler next;
            bool isFindValue = false;
        };

        struct iterator
        {
            const AsyncGenerator* owner;
            Task<iterator> operator++()
            {

                owner->coro.promise().isFindValue = false;
                while (owner->findValue()) {
                    co_yield{};
                }
                co_return *this;
            }
            decltype(auto) operator*()
            {
                return owner->coro.promise().value;
            }
            bool operator!=(const iterator&) const
            {
                return (!owner || !owner->coro.done());
            }
            auto next() {
                return ++(*this);
            }
        };
    public:
        Task<iterator> begin() const
        {
            coro.promise().isFindValue = false;
            while (this->findValue()) {
                co_yield{};
            }
            co_return iterator{ this };
        }
        iterator end()const { return { nullptr }; }

        template<class Func>
        Task<void> each(Func func) const requires std::is_invocable_v<Func, Type>
        {
            auto it = co_await this->begin();
            auto endIt = this->end();
            for (; it != endIt; it = co_await ++it) {
                func(*it);
            }
        }
    public:
        explicit AsyncGenerator(handle h)
            : coro(h)
        {}

        AsyncGenerator(const AsyncGenerator&) = delete;

        AsyncGenerator(AsyncGenerator&& rhs) noexcept
            : coro(std::move(rhs.coro))
        {
            rhs.coro = nullptr;
        }

        ~AsyncGenerator()
        {
            if (coro) {
                coro.destroy();
            }
        }
    private:
        bool findValue() const
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

                    if (!next.moveNext()) {
                        next.clear();
                    } else {
                        return true;
                    }
                }
            }
            coro.resume();
            return !coro.promise().isFindValue && !coro.done();
        }
    private:
        handle coro;
    };
}