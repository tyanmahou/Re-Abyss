#pragma once
#include <Siv3D.hpp>

namespace abyss::Math
{
    inline constexpr double Epsilon = 0.001;
    inline bool IsZeroLoose(double x)
    {
        return -Epsilon < x && x < Epsilon;
    }

    inline bool IsZeroLoose(const s3d::Vec2& v)
    {
        return IsZeroLoose(v.x) && IsZeroLoose(v.y);
    }

    /// <summary>
    /// 2点を通る直線を求める
    /// </summary>
    /// <param name="p1"></param>
    /// <param name="p2"></param>
    /// <returns></returns>
    inline auto LinearFunc(const s3d::Vec2& p1, const s3d::Vec2& p2)
    {
        const double a = (p2.y - p1.y) / (p2.x - p1.x);
        const double b = p1.y - a * p1.x;
        return [a, b](double x) {
            return a * x + b;
        };
    }
}