#pragma once
#include <abyss/commons/Constants.hpp>

namespace abyss
{
    class PivotUtil
    {
    public:
        static constexpr s3d::Vec2 FromCenter(const s3d::Vec2& pos)
        {
            return pos + Constants::AppResolution / 2.0;
        }
    };
}