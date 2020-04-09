#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
namespace abyss
{
    struct LaunSharkShotParam
    {
        TOML_BIND_BEGIN;

        [[TOML_BIND_PARAM(Base::Hp, "Base.hp")]]
        [[TOML_BIND_PARAM(Base::Size, "Base.size")]]
        struct Base
        {
            inline static s3d::int32 Hp{ 4 };
            inline static s3d::Vec2 Size{ 30, 10 };
        };

        [[TOML_BIND_PARAM(Wait::Time, "Pursuit.time")]]
        [[TOML_BIND_PARAM(Wait::Speed, "Pursuit.speed")]]
        struct Wait
        {
            inline static double Time{ 2.0 };
            inline static double Speed{ 20.0 };
        };

        [[TOML_BIND_PARAM(Pursuit::Time, "Pursuit.time")]]
        [[TOML_BIND_PARAM(Pursuit::RotateDeg, "Pursuit.rotateDeg")]]
        [[TOML_BIND_PARAM(Pursuit::Speed, "Pursuit.speed")]]
        struct Pursuit
        {
            inline static double Time{ 2.0 };
            inline static double RotateDeg{ 60.0 };
            inline static double Speed{ 20.0 };
        };

        [[TOML_BIND_PARAM(Firinged::Accel, "Firinged.accel")]]
        [[TOML_BIND_PARAM(Firinged::MaxSpeed, "Firinged.maxSpeed")]]
        struct Firinged
        {
            inline static double Accel{ 120.0 };
            inline static double MaxSpeed{ 360.0 };
        };

        [[TOML_BIND_PARAM(View::AnimeTimeSec, "View.animeTimeSec")]]
        struct View
        {
            inline static double AnimeTimeSec{ 0.25 };
        };

        TOML_BIND_END;
    };
}