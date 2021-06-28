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
}