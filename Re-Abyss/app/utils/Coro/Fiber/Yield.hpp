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
}
