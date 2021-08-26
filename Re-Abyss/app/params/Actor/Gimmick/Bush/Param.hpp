#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss::Actor::Gimmick::Bush
{
    struct Param
    {
        [[TOML_BIND(TimeOffsetFactor, "timeOffsetFactor")]]
        inline static double TimeOffsetFactor = 10.0;

        [[TOML_BIND(AnimTimeSec, "animTimeSec")]]
        inline static double AnimTimeSec = 2.0;

        [[TOML_BIND(HitTimeScale, "hitTimeScale")]]
        inline static double HitTimeScale = 2.0;
    };
}