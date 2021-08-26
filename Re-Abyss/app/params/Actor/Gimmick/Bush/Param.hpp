#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
#include <Siv3D/Vector2D.hpp>

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

        [[TOML_BIND(ColliderSize, "colliderSize")]]
        inline static s3d::Vec2 ColliderSize{};

        [[TOML_BIND(ColliderOffset, "colliderOffset")]]
        inline static s3d::Vec2 ColliderOffset{};
    };
}