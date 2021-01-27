#pragma once
#include <coroutine>

namespace abyss::Coro
{
    template<class Type>
    struct Generator
    {
        struct promise_type;
        using handle = std::coroutine_handle<promise_type>;

        struct promise_type
        {
            Type value;
            auto get_return_object() { return Generator{ handle::from_promise(*this) }; }
            auto  initial_suspend() { return std::suspend_never{}; }
            auto final_suspend() { return std::suspend_always{}; }
            auto yield_value(const Type& _value)
            {
                this->value = _value;
                return std::suspend_always{};
            }
            void unhandled_exception() { std::terminate(); }
            void return_void() {}
        };

        struct iterator
        {
            const Generator* owner;
            iterator& operator++()
            {
                if (!owner->coro.done()) {
                    owner->coro.resume();
                }
                return *this;
            }
            decltype(auto) operator*()
            {
                return owner->coro.promise().value;
            }
            bool operator!=(const iterator&) const
            {
                return (!owner || !owner->coro.done());
            }
        };

        iterator begin()const { return { this }; }
        iterator end()const { return { nullptr }; }
    public:
        explicit Generator(handle h)
            : coro(h)
        {}

        Generator(Generator const&) = delete;

        Generator(Generator&& rhs) noexcept
            : coro(std::move(rhs.coro))
        {
            rhs.coro = nullptr;
        }

        ~Generator()
        {
            if (coro) {
                coro.destroy();
            }
        }
    private:
        handle coro;
    };
}