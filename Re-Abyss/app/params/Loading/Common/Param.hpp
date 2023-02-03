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
            inline static s3d::Vec2 BasePos{ -260, -40 };
            inline static double PeriodicSec{ 1.3 };
            inline static double JumpSec{ 1.0 };
        };

        [[TOML_BIND(Text::BasePos, "Text.basePos")]]
        [[TOML_BIND(Text::OffsetX, "Text.offsetX")]]
        [[TOML_BIND(Text::PeriodicSec, "Text.periodicSec")]]
        [[TOML_BIND(Text::JumpPeriodicOffset, "Text.jumpPeriodicOffset")]]
        [[TOML_BIND(Text::JumpIndexCoef, "Text.jumpIndexCoef")]]
        [[TOML_BIND(Text::JumpTimeRate, "Text.jumpTimeRate")]]
        [[TOML_BIND(Text::JumpHeight, "Text.jumpHeight")]]
        [[TOML_BIND(Text::RotatePeriodicOffset, "Text.rotatePeriodicOffset")]]
        [[TOML_BIND(Text::RotateIndexCoef, "Text.rotateIndexCoef")]]
        [[TOML_BIND(Text::RotateTimeRate, "Text.rotateTimeRate")]]
        struct Text
        {
            inline static s3d::Vec2 BasePos{ -220, -54 };
            inline static double OffsetX{ 1.0 };
            inline static double PeriodicSec{ 3.9 };
            inline static double JumpPeriodicOffset{ -0.15 };
            inline static double JumpIndexCoef{ 15.0 };
            inline static double JumpTimeRate{ 0.2 };
            inline static double JumpHeight{ 20 };

            inline static double RotatePeriodicOffset{ -1.3 };
            inline static double RotateIndexCoef{ 8.0 };
            inline static double RotateTimeRate{ 0.2 };
        };

        [[TOML_BIND(ProgressBar::BasePos, "ProgressBar.basePos")]]
        [[TOML_BIND(ProgressBar::Size, "ProgressBar.size")]]
        struct ProgressBar
        {
            inline static s3d::Vec2 BasePos{ -220, -25 };
            inline static s3d::Vec2 Size{ 200, 5 };
        };
    };
}
