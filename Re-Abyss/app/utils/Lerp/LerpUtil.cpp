#include "LerpUtil.hpp"
#include <Siv3D.hpp>

namespace abyss::LerpUtil
{
    double Ratio(double ratio, double dt)
    {
        ratio = s3d::Saturate(ratio);
        return 1.0 - s3d::Pow(1.0 - ratio, 60.0 * dt);
    }
}
