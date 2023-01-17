#pragma once
#include <abyss/utils/TOML/TOMLBind.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Actor::Player
{
    struct Param
    {
        [[TOML_BIND(Base::Hp, "Base.hp")]]
        [[TOML_BIND(Base::InvincibleTime, "Base.invincibleTime")]]
        [[TOML_BIND(Base::Size, "Base.size")]]
        struct Base
        {
            inline static s3d::int32 Hp{ 8 };
            inline static double InvincibleTime{ 2.0 };
            inline static s3d::Vec2 Size{ 22, 80 };
        };

        [[TOML_BIND(Swim::AccelX, "Swim.accelX")]]
        [[TOML_BIND(Swim::DecelX, "Swim.decelX")]]
        [[TOML_BIND(Swim::MaxSpeedX, "Swim.maxSpeedX")]]
        [[TOML_BIND(Swim::DiveSpeed, "Swim.diveSpeed")]]
        [[TOML_BIND(Swim::JumpHeight, "Swim.jumpHeight")]]
        struct Swim
        {
            inline static double AccelX{ 360.0 };
            inline static double DecelX{ 180.0 };
            inline static double MaxSpeedX{ 240.0 };
            inline static double DiveSpeed{ 150.0 };
            inline static double JumpHeight{ 90.0 };
        };

        [[TOML_BIND(Ladder::Speed, "Ladder.speed")]]
        struct Ladder
        {
            inline static double Speed{ 120.0 };
        };

        [[TOML_BIND(Damage::TimeSec, "Damage.timeSec")]]
        [[TOML_BIND(Damage::KnockBackSpeed, "Damage.knockBackSpeed")]]
        struct Damage
        {
            inline static double TimeSec{ 0.5 };
            inline static s3d::Vec2 KnockBackSpeed{ 210, 210 };
        };

        [[TOML_BIND(Dead::TimeSec, "Dead.timeSec")]]
        [[TOML_BIND(Dead::AnimeTimeSec, "Dead.animeTimeSec")]]
        [[TOML_BIND(Dead::KnockBackSpeed, "Dead.knockBackSpeed")]]
        struct Dead
        {
            inline static double TimeSec{ 0.5 };
            inline static double AnimeTimeSec{ 0.5 };
            inline static s3d::Vec2 KnockBackSpeed{ 210, 210 };
        };

    };
}