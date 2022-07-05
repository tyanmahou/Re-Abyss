#include <abyss/utils/Easing/EasingUtil.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    double EasingUtil::Stairs(double rate0_1, double span)
    {
        if (rate0_1 <= 0.0) {
            return 0.0;
        }
        if (rate0_1 >= 1.0) {
            return 1.0;
        }
        return s3d::Floor(rate0_1 / span) * span;
    }
    double EasingUtil::StairsDivide(double rate0_1, s3d::int32 divide)
    {
        if (rate0_1 <= 0.0) {
            return 0.0;
        }
        if (rate0_1 >= 1.0) {
            return 1.0;
        }
        return s3d::Floor(rate0_1 * divide) / static_cast<double>(divide);
    }
}
