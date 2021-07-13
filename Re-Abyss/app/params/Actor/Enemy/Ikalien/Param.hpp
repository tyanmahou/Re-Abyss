#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss::Actor::Enemy::Ikalien
{
    struct Param
    {
        [[TOML_BIND(Base::Hp, "Base.hp")]]
        [[TOML_BIND(Base::Pivot, "Base.pivot")]]
        [[TOML_BIND(Base::ColRadius, "Base.colRadius")]]
        struct Base
        {
            inline static s3d::int32 Hp{ 6 };
            inline static s3d::Vec2 Pivot{ 0, -15 };
            inline static double ColRadius = 18;
        };

        [[TOML_BIND(Pursuit::Time, "Pursuit.time")]]
        [[TOML_BIND(Pursuit::RotateDeg, "Pursuit.rotateDeg")]]
        [[TOML_BIND(Pursuit::Speed, "Pursuit.speed")]]
        struct Pursuit
        {
            inline static double Time{ 2.0 };
            inline static double RotateDeg{ 60.0 };
            inline static double Speed{ 30.0 };
        };

        [[TOML_BIND(Swim::Speed, "Swim.speed")]]
        [[TOML_BIND(Swim::Decel, "Swim.decel")]]
        struct Swim
        {
            inline static double Speed{ 360.0 };
            inline static double Decel{ 360.0 };
        };

        [[TOML_BIND(View::WaitAnimeTimeSec, "View.waitAnimeTimeSec")]]
        struct View
        {
            inline static double WaitAnimeTimeSec{ 1.5 };
        };
    };
}