#include <abyss/utils/Random/RandUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::Random
{
    double RandUtil::ProbabilityIterative(double p, double dt, const Fps& baseFps)
    {
        return 1.0 - s3d::Pow(1.0 - p, baseFps.frame(dt));
    }
    bool RandUtil::RandomBoolIterative(double p, double dt, const Fps& baseFps)
    {
        return s3d::RandomBool(ProbabilityIterative(p, dt, baseFps));
    }
}
