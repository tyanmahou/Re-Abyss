#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Player
{
    struct Param
    {
        [[TOML_BIND_PARAM(Base::Hp, "Base.hp")]]
        [[TOML_BIND_PARAM(Base::InvincibleTime, "Base.invincibleTime")]]
        [[TOML_BIND_PARAM(Base::Size, "Base.size")]]
        struct Base
        {
            inline static s3d::int32 Hp{ 8 };
            inline static double InvincibleTime{ 2.0 };
            inline static s3d::Vec2 Size{ 22, 80 };
        };

        [[TOML_BIND_PARAM(Swim::AccelX, "Swim.accelX")]]
        [[TOML_BIND_PARAM(Swim::DecelX, "Swim.decelX")]]
        [[TOML_BIND_PARAM(Swim::MaxSpeedX, "Swim.maxSpeedX")]]
        [[TOML_BIND_PARAM(Swim::DiveSpeed, "Swim.diveSpeed")]]
        [[TOML_BIND_PARAM(Swim::JumpHeight, "Swim.jumpHeight")]]
        struct Swim
        {
            inline static double AccelX{ 360.0 };
            inline static double DecelX{ 180.0 };
            inline static double MaxSpeedX{ 240.0 };
            inline static double DiveSpeed{ 150.0 };
            inline static double JumpHeight{ 90.0 };
        };

        [[TOML_BIND_PARAM(Ladder::Speed, "Ladder.speed")]]
        struct Ladder
        {
            inline static double Speed{ 120.0 };
        };

        [[TOML_BIND_PARAM(Damage::TimeSec, "Damage.timeSec")]]
        [[TOML_BIND_PARAM(Damage::KnockBackSpeed, "Damage.knockBackSpeed")]]
        struct Damage
        {
            inline static double TimeSec{ 0.5 };
            inline static s3d::Vec2 KnockBackSpeed{ 210, 210 };
        };

        [[TOML_BIND_PARAM(Dead::TimeSec, "Dead.timeSec")]]
        [[TOML_BIND_PARAM(Dead::KnockBackSpeed, "Dead.knockBackSpeed")]]
        struct Dead
        {
            inline static double TimeSec{ 0.5 };
            inline static s3d::Vec2 KnockBackSpeed{ 210, 210 };
        };

    };
}