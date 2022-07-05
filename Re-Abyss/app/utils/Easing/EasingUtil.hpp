#pragma once
#include <Siv3D/Types.hpp>

namespace abyss
{
    class EasingUtil
    {
    public:
        static double Floor(double rate0_1, double span);
        static double FloorDivide(double rate0_1, s3d::int32 divide);

        static double Ceil(double rate0_1, double span);
        static double CeilDivide(double rate0_1, s3d::int32 divide);
    };
}
