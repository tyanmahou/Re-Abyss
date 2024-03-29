#pragma once
#include <abyss/values/Fps.hpp>

namespace abyss::Random
{
    class RandUtil
    {
    public:
        /// <summary>
        /// DeltaTimeを考慮した、反復試行確率
        /// </summary>
        /// <param name="p"></param>
        /// <param name="dt"></param>
        /// <param name="baseFps"></param>
        /// <returns></returns>
        static double ProbabilityIterative(double p, double dt, const Fps& baseFps = 60_fps);

        /// <summary>
        /// DeltaTimeを考慮した、反復試行乱数
        /// </summary>
        /// <param name="p"></param>
        /// <param name="dt"></param>
        /// <returns></returns>
        static bool RandomBoolIterative(double p, double dt, const Fps& baseFps = 60_fps);
    };
}
