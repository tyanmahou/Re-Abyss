#pragma once

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
        template<class Handle>
        concept YieldAwaitableHandle = requires(Handle handle)
        {
            requires std::same_as<Yield, decltype(handle.promise().yield)>;
            requires std::convertible_to<Handle, std::coroutine_handle<>>;
        };

        struct YieldAwaiter
        {
            bool await_ready() const noexcept
            {
                return yield.count == 0;
            }

            template<YieldAwaitableHandle Handle>
            void await_suspend(Handle handle)
            {
                --(handle.promise().yield = yield).count;
            }
            void await_resume() {}

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
