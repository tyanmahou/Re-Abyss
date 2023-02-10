#include <abyss/utils/Random/RandUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::Random
{
    double RandUtil::ProbabilityIterative(double p, double dt, double baseFps)
    {
        return 1.0 - s3d::Pow(1.0 - p, dt * baseFps);
    }
    bool RandUtil::RandomBoolIterative(double p, double dt, double baseFps)
    {
        return s3d::RandomBool(ProbabilityIterative(p, dt, baseFps));
    }
}
