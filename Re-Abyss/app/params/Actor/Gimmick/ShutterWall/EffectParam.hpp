#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss::Actor::Gimmick::ShutterWall
{
    struct EffectParam
    {
        [[TOML_BIND(InitSpeedMin, "initSpeedMin")]]
        inline static double InitSpeedMin{ 400.0 };

        [[TOML_BIND(InitSpeedMax, "initSpeedMax")]]
        inline static double InitSpeedMax{ 580.0 };

        [[TOML_BIND(InitVelocityAngleRange, "initVelocityAngleRange")]]
        inline static double InitVelocityAngleRange{ 60.0 };

        [[TOML_BIND(DecelH, "decelH")]]
        inline static double DecelH{ 360.0 };

        [[TOML_BIND(Gravity, "gravity")]]
        inline static double Gravity{ 720.0 };

        [[TOML_BIND(MaxSpeedV, "maxSpeedV")]]
        inline static double MaxSpeedV{ 300.0 };

        [[TOML_BIND(LifeTime, "lifeTime")]]
        inline static double LifeTime{ 1.0 };

        [[TOML_BIND(TimeScale, "timeScale")]]
        inline static double TimeScale{ 1.2 };
    };
}
