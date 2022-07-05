#pragma once
#include <Siv3D/Types.hpp>

namespace abyss
{
    class EasingUtil
    {
    public:
        static double Stairs(double rate0_1, double span);
        static double StairsDivide(double rate0_1, s3d::int32 divide);
    };
}
