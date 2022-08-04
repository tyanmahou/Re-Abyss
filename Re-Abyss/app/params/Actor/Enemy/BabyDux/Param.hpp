#pragma once
#include <abyss/params/Actor/Enemy/BabyDux/BabyDesc.hpp>

namespace abyss::Actor::Enemy::BabyDux
{
    struct Param
    {
        [[TOML_BIND(Base::Hp, "Base.hp")]]
        [[TOML_BIND(Base::EyeL, "Base.eyeL")]]
        [[TOML_BIND(Base::EyeR, "Base.eyeR")]]
        [[TOML_BIND(Base::Pivot, "Base.pivot")]]
        [[TOML_BIND(Base::Size, "Base.size")]]
        struct Base
        {
            inline static s3d::int32 Hp{ 6 };
            inline static s3d::Vec2 EyeL{ -14, -2 };
            inline static s3d::Vec2 EyeR{ 9, -2 };

            inline static s3d::Vec2 Pivot{ 0, -15 };
            inline static s3d::Vec2 Size{ 20, 20};
        };

        [[TOML_BIND(Move::Gravity, "Move.gravity")]]
        [[TOML_BIND(Move::JumpHeight, "Move.jumpHeight")]]
        [[TOML_BIND(Move::MaxSpeedY, "Move.maxSpeedY")]]
        [[TOML_BIND(Move::DecelX, "Move.decelX")]]
        [[TOML_BIND(Move::MoveX, "Move.moveX")]]
        [[TOML_BIND(Move::ChargeTimeSec, "Move.chargeTimeSec")]]
        [[TOML_BIND(Move::ChargeOffs, "Move.chargeOffs")]]
        struct Move
        {
            inline static double Gravity{400};
            inline static double JumpHeight{ 300 };
            inline static double MaxSpeedY{ 78 };
            inline static double DecelX{ 20 };
            inline static double MoveX{ 200 };
            inline static double ChargeTimeSec{ 0.5 };
            inline static double ChargeOffs{ 50 };
        };
        [[TOML_BIND(Eye::DistRate, "Eye.dist")]]
        [[TOML_BIND(Eye::DistRate, "Eye.distRate")]]
        [[TOML_BIND(Eye::ErpRate, "Eye.erpRate")]]
        [[TOML_BIND(Eye::LimitBeginL, "Eye.limitBeginL")]]
        [[TOML_BIND(Eye::LimitEndL, "Eye.limitEndL")]]
        [[TOML_BIND(Eye::LimitBeginR, "Eye.limitBeginR")]]
        [[TOML_BIND(Eye::LimitEndR, "Eye.limitEndR")]]
        struct Eye
        {
            inline static double Dist{ 6.0 };
            inline static double DistRate{ 0.005 };
            inline static double ErpRate{ 0.02 };

            inline static s3d::Vec2 LimitBeginL{ 108, 155 };
            inline static s3d::Vec2 LimitEndL{ 108, 155 };
            inline static s3d::Vec2 LimitBeginR{ 108, 155 };
            inline static s3d::Vec2 LimitEndR{ 108, 155 };
        };
    };
}
