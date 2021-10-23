#pragma once
#include <coroutine>

namespace abyss::Coro
{
    struct IteratorEnd{};

    template<class Type>
    struct Iterator
    {
        struct promise_type
        {
            Type value;
            auto get_return_object() { return Iterator{ handle::from_promise(*this) }; }
            auto  initial_suspend() { return std::suspend_never{}; }
            auto final_suspend() noexcept { return std::suspend_always{}; }
            auto yield_value(const Type& _value)
            {
                this->value = _value;
                return std::suspend_always{};
            }
            void unhandled_exception() { std::terminate(); }
            void return_void() {}
        };

        using handle = std::coroutine_handle<promise_type>;

    public:
        explicit Iterator(handle h)
            : coro(h)
        {}

        Iterator(Iterator const&) = delete;

        Iterator(Iterator&& rhs) noexcept
            : coro(std::move(rhs.coro))
        {
            rhs.coro = nullptr;
        }

        ~Iterator()
        {
            if (coro) {
                coro.destroy();
            }
        }
        Iterator& operator++()
        {
            if (!coro.done()) {
                coro.resume();
            }
            return *this;
        }
        decltype(auto) operator*()
        {
            return coro.promise().value;
        }
        bool operator!=(const IteratorEnd&) const
        {
            return !coro.done();
        }
    private:
        handle coro;
    };
}