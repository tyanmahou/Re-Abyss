#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss::RollingTako
{
    struct Param
    {
        TOML_BIND_BEGIN;

        [[TOML_BIND_PARAM(Base::Hp, "Base.hp")]]
        [[TOML_BIND_PARAM(Base::Size, "Base.size")]]
        [[TOML_BIND_PARAM(Base::Pivot, "Base.pivot")]]
        struct Base
        {
            inline static s3d::int32 Hp{ 6 };
            inline static s3d::Vec2 Size{ 45, 45 };
            inline static s3d::Vec2 Pivot{ 0, 7.5 };
        };

        [[TOML_BIND_PARAM(Wait::SearchRange, "Wait.searchRange")]]
        struct Wait
        {
            inline static double SearchRange{ 300 };
        };

        [[TOML_BIND_PARAM(Run::AccelX, "Run.accelX")]]
        [[TOML_BIND_PARAM(Run::MaxSpeedX, "Run.maxSpeedX")]]
        struct Run
        {
            inline static double AccelX{ 180 };
            inline static double MaxSpeedX{ 200 };
        };

        [[TOML_BIND_PARAM(View::WaitAnimeTimeSec, "View.waitAnimeTimeSec")]]
        [[TOML_BIND_PARAM(View::RunAnimeTimeSec, "View.runAnimeTimeSec")]]
        struct View
        {
            inline static double WaitAnimeTimeSec{ 1.0 };
            inline static double RunAnimeTimeSec{ 0.2 };
        };

        TOML_BIND_END;
    };
}