#pragma once
#include <coroutine>
#include <abyss/utils/Coro/Fiber/IAwaiter.hpp>

namespace abyss::Coro
{
    /// <summary>
    /// Yield
    /// </summary>
    struct Yield
    {
        constexpr Yield() :
            count(1)
        {}

        constexpr Yield(std::uint32_t _count) :
            count(_count)
        {}

        std::uint32_t count;
    };

    namespace detail
    {
        struct YieldAwaiter : IAwaiter
        {
            YieldAwaiter(const Yield& y):
                yield(y)
            {}
            bool await_ready() const noexcept
            {
                return yield.count == 0;
            }

            template<AwaitableHandler Handle>
            void await_suspend(Handle handle)
            {
                handle.promise().pAwaiter = this;
            }
            void await_resume() {}

            bool resume() override
            {
                return --yield.count > 0;
            }
            Yield yield;
        };
    }

    /// <summary>
    /// operator co_await
    /// </summary>
    /// <param name="yield"></param>
    /// <returns></returns>
    inline auto operator co_await(const Yield& yield)
    {
        return detail::YieldAwaiter{ yield };
    }
}
