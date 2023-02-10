#pragma once
#include <abyss/values/Fps.hpp>

namespace abyss::InterpUtil
{
    /// <summary>
    /// デルタタイムを考慮して、補間率
    /// </summary>
    double DampRatio(double ratio, double dt, const Fps& baseFps = 60_fps);

    template <class T, class U, class V>
    inline auto LerpDeg(const T from, const U to, const V t) noexcept
    {
        const auto diff = std::fmod(to - from, static_cast<CommonFloat_t<T, U>>(360.0));
        return (from + (std::fmod(2 * diff, static_cast<CommonFloat_t<T, U>>(360.0)) - diff) * t);
    }
}
