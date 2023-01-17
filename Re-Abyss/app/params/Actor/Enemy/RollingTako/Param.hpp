#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOML/TOMLBind.hpp>

namespace abyss::Actor::Enemy::RollingTako
{
    struct Param
    {
        [[TOML_BIND(Base::Hp, "Base.hp")]]
        [[TOML_BIND(Base::Size, "Base.size")]]
        [[TOML_BIND(Base::Pivot, "Base.pivot")]]
        struct Base
        {
            inline static s3d::int32 Hp{ 6 };
            inline static s3d::Vec2 Size{ 45, 45 };
            inline static s3d::Vec2 Pivot{ 0, 7.5 };
        };

        [[TOML_BIND(Wait::SearchRange, "Wait.searchRange")]]
        struct Wait
        {
            inline static double SearchRange{ 300 };
        };

        [[TOML_BIND(Run::AccelX, "Run.accelX")]]
        [[TOML_BIND(Run::MaxSpeedX, "Run.maxSpeedX")]]
        struct Run
        {
            inline static double AccelX{ 180 };
            inline static double MaxSpeedX{ 200 };
        };

        [[TOML_BIND(View::WaitAnimeTimeSec, "View.waitAnimeTimeSec")]]
        [[TOML_BIND(View::RunAnimeTimeSec, "View.runAnimeTimeSec")]]
        struct View
        {
            inline static double WaitAnimeTimeSec{ 1.0 };
            inline static double RunAnimeTimeSec{ 0.2 };
        };
    };
}