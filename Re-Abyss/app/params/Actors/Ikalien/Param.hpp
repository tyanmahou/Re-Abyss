#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss::Ikalien
{
    struct Param
    {
        TOML_BIND_BEGIN;

        [[TOML_BIND_PARAM(Base::Hp, "Base.hp")]]
        [[TOML_BIND_PARAM(Base::Pivot, "Base.pivot")]]
        [[TOML_BIND_PARAM(Base::ColRadius, "Base.colRadius")]]
        struct Base
        {
            inline static s3d::int32 Hp{ 6 };
            inline static s3d::Vec2 Pivot{ 0, -15 };
            inline static double ColRadius = 18;
        };

        [[TOML_BIND_PARAM(Pursuit::Time, "Pursuit.time")]]
        [[TOML_BIND_PARAM(Pursuit::RotateDeg, "Pursuit.rotateDeg")]]
        [[TOML_BIND_PARAM(Pursuit::Speed, "Pursuit.speed")]]
        struct Pursuit
        {
            inline static double Time{ 2.0 };
            inline static double RotateDeg{ 60.0 };
            inline static double Speed{ 30.0 };
        };

        [[TOML_BIND_PARAM(Swim::Speed, "Swim.speed")]]
        [[TOML_BIND_PARAM(Swim::Deccel, "Swim.deccel")]]
        struct Swim
        {
            inline static double Speed{ 360.0 };
            inline static double Deccel{ 360.0 };
        };

        [[TOML_BIND_PARAM(View::WaitAnimeTimeSec, "View.waitAnimeTimeSec")]]
        struct View
        {
            inline static double WaitAnimeTimeSec{ 1.5 };
        };

        TOML_BIND_END;
    };
}