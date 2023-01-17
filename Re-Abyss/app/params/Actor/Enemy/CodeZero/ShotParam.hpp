#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOML/TOMLBind.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    struct ShotParam
    {
        [[TOML_BIND(Base::ColRadius, "Base.colRadius")]]
        struct Base
        {
            inline static double ColRadius{ 70.0 };
        };

        [[TOML_BIND(Wait::ScaleTime, "Wait.scaleTime")]]
        struct Wait
        {
            inline static double ScaleTime{ 3.0 };
        };

        [[TOML_BIND(Pursuit::Speed, "Pursuit.speed")]]
        [[TOML_BIND(Pursuit::TimeSec, "Pursuit.timeSec")]]
        [[TOML_BIND(Pursuit::EndToDeadTimeSec, "Pursuit.endToDeadTimeSec")]]
        struct Pursuit
        {
            inline static double Speed{ 90.0 };
            inline static double TimeSec{ 5.0 };
            inline static double EndToDeadTimeSec{ 3.5 };
        };
    };
}