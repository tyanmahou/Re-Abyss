#pragma once
#include <coroutine>
#include <abyss/utils/Coro/Fiber/Fiber.hpp>

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
            void unhandled_exception() { std::terminate(); }
            void return_void() {}
            IAwaiter* pAwaiter = nullptr;
            bool isFindValue = false;
        };

        struct iterator
        {
            const AsyncGenerator* owner;
            Fiber<iterator> operator++() const
            {
                owner->m_coro.promise().isFindValue = false;
                while (owner->findValue()) {
                    co_yield{};
                }
                co_return *this;
            }
            decltype(auto) operator*() const
            {
                return owner->m_coro.promise().value;
            }
            bool operator!=(const iterator&) const
            {
                return (!owner || !owner->m_coro.done());
            }
        };
    public:
        Fiber<iterator> begin() const
        {
            m_coro.promise().isFindValue = false;
            while (this->findValue()) {
                co_yield{};
            }
            co_return iterator{ this };
        }
        iterator end()const { return { nullptr }; }

        template<class Func>
        Fiber<void> each(Func func) const requires std::is_invocable_v<Func, Type>
        {
            auto it = co_await this->begin();
            auto endIt = this->end();
            for (; it != endIt; it = co_await ++it) {
                func(*it);
            }
        }
    public:
        explicit AsyncGenerator(handle h)
            : m_coro(h)
        {}

        AsyncGenerator(const AsyncGenerator&) = delete;

        AsyncGenerator(AsyncGenerator&& rhs) noexcept
            : m_coro(std::move(rhs.m_coro))
        {
            rhs.m_coro = nullptr;
        }

        ~AsyncGenerator()
        {
            if (m_coro) {
                m_coro.destroy();
            }
        }
    private:
        bool findValue() const
        {
            if (!m_coro) {
                return false;
            }
            if (m_coro.done()) {
                return false;
            }
            // Yield
            {
                if (auto& pAwaiter = m_coro.promise().pAwaiter) {
                    if (!pAwaiter->resume()) {
                        pAwaiter = nullptr;
                    } else {
                        return true;
                    }
                }
            }
            m_coro.resume();
            return !m_coro.promise().isFindValue && !m_coro.done();
        }
    private:
        handle m_coro;
    };
}
