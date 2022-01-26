#include <abyss/utils/Interp/InterpUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::InterpUtil
{
    double DampRatio(double ratio, double dt, double baseFps)
    {
        return 1.0 - s3d::Pow(1.0 - ratio, baseFps * dt);
    }
}
