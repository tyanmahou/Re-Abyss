#pragma once
#include <tuple>
#include <coroutine>

namespace abyss::Coro
{
    namespace detail
    {
        template <class F, typename Tuple, size_t... Is>
        auto TupleTransformImpl(Tuple t, F f, std::index_sequence<Is...>)
        {
            return std::tuple<decltype(f(std::get<Is>(t)))...>(f(std::get<Is>(t))...);
        }

        template <class F, typename... Args>
        auto TupleTransform(const std::tuple<Args...>& t, F f)
        {
            return TupleTransformImpl(t, f, std::make_index_sequence<sizeof...(Args)>{});
        }
    }

    template<class It>
    struct Enumerator
    {
        struct promise_type;
        using handle = std::coroutine_handle<promise_type>;

        struct promise_type
        {
            It it;
            auto get_return_object() { return Enumerator{ handle::from_promise(*this) }; }
            auto  initial_suspend() { return std::suspend_never{}; }
            auto final_suspend() { return std::suspend_always{}; }
            auto yield_value(It it)
            {
                this->it = it;
                return std::suspend_always{};
            }
            void unhandled_exception() { std::terminate(); }
            void return_void() {}
        };

        struct iterator
        {
            Enumerator* owner;
            iterator& operator++()
            {
                if (!owner->coro.done()) {
                    owner->coro.resume();
                }
                return *this;
            }
            decltype(auto) operator*()
            {
                return *(owner->coro.promise().it);
            }
            bool operator!=(const iterator&) const
            {
                return (!owner || !owner->coro.done());
            }
        };

        iterator begin() { return { this }; }
        iterator end() { return { nullptr }; }
    public:
        explicit Enumerator(handle h)
            : coro(h)
        {}

        Enumerator(Enumerator const&) = delete;

        Enumerator(Enumerator&& rhs) noexcept
            : coro(std::move(rhs.coro))
        {
            rhs.coro = nullptr;
        }

        ~Enumerator()
        {
            if (coro) {
                coro.destroy();
            }
        }
    private:
        handle coro;
    };

    /// <summary>
    /// 複数イテレータに特殊化
    /// </summary>
    template<class... It>
    struct Enumerator<std::tuple<It...>>
    {
        struct promise_type;
        using handle = std::coroutine_handle<promise_type>;

        struct promise_type
        {
            std::tuple<It...> it;
            auto get_return_object() { return Enumerator{ handle::from_promise(*this) }; }
            auto  initial_suspend() { return std::suspend_never{}; }
            auto final_suspend() { return std::suspend_always{}; }
            auto yield_value(std::tuple<It...> it)
            {
                this->it = it;
                return std::suspend_always{};
            }
            void unhandled_exception() { std::terminate(); }
            void return_void() {}
        };

        struct iterator
        {
            Enumerator* owner;
            iterator& operator++()
            {
                if (!owner->coro.done()) {
                    owner->coro.resume();
                }
                return *this;
            }
            decltype(auto) operator*()
            {
                return detail::TupleTransform(
                    owner->coro.promise().it, 
                    [](auto& it)->decltype(auto) {return *it; }
                );
            }
            bool operator!=(const iterator&) const
            {
                return (!owner || !owner->coro.done());
            }
        };

        iterator begin() { return { this }; }
        iterator end() { return { nullptr }; }
    public:
        explicit Enumerator(handle h)
            : coro(h)
        {}

        Enumerator(Enumerator const&) = delete;

        Enumerator(Enumerator&& rhs) noexcept
            : coro(std::move(rhs.coro))
        {
            rhs.coro = nullptr;
        }

        ~Enumerator()
        {
            if (coro) {
                coro.destroy();
            }
        }
    private:
        handle coro;
    };
}