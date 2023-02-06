#pragma once
#include <abyss/utils/TOML/TOMLBind.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Loading::Common
{
    struct Param
    {
        [[TOML_BIND(Slime::BasePos, "Slime.basePos")]]
        [[TOML_BIND(Slime::PeriodicSec, "Slime.periodicSec")]]
        [[TOML_BIND(Slime::JumpSec, "Slime.jumpSec")]]
        struct Slime
        {
            inline static s3d::Vec2 BasePos{ -60, -40 };
            inline static double PeriodicSec{ 1.3 };
            inline static double JumpSec{ 1.0 };
        };
    };
}
