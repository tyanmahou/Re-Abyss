#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Cycle
{
    struct LoadingParam
    {
        [[TOML_BIND_PARAM(Slime::BasePos, "Slime.basePos")]]
        [[TOML_BIND_PARAM(Slime::PeriodicSec, "Slime.periodicSec")]]
        [[TOML_BIND_PARAM(Slime::JumpSec, "Slime.jumpSec")]]
        struct Slime
        {
            inline static s3d::Vec2 BasePos{ 700, 500 };
            inline static double PeriodicSec{ 1.3 };
            inline static double JumpSec{ 1.0 };
        };

        [[TOML_BIND_PARAM(Text::BasePos, "Text.basePos")]]
        [[TOML_BIND_PARAM(Text::OffsetX, "Text.offsetX")]]
        [[TOML_BIND_PARAM(Text::PeriodicSec, "Text.periodicSec")]]
        [[TOML_BIND_PARAM(Text::JumpPeriodicOffset, "Text.jumpPeriodicOffset")]]
        [[TOML_BIND_PARAM(Text::JumpIndexCoef, "Text.jumpIndexCoef")]]
        [[TOML_BIND_PARAM(Text::JumpTimeRate, "Text.jumpTimeRate")]]
        [[TOML_BIND_PARAM(Text::JumpHeight, "Text.jumpHeight")]]
        struct Text
        {
            inline static s3d::Vec2 BasePos{ 900, 540 };
            inline static double OffsetX{ 5.0 };
            inline static double PeriodicSec{ 2.0 };
            inline static double JumpPeriodicOffset{ 2.0 };
            inline static double JumpIndexCoef{ 2.0 };
            inline static double JumpTimeRate{ 2.0 };
            inline static double JumpHeight{ 2.0 };
        };
    };
}