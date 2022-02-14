#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    struct BabyDesc
    {
        [[TOML_BIND(waitTimeSec)]]
        double waitTimeSec{ 0 };
        [[TOML_BIND(offset)]]
        s3d::Vec2 offset{ 0, 0 };
        [[TOML_BIND(appearTime)]]
        double appearTime{ 2.0 };
        [[TOML_BIND(appearMove)]]
        s3d::Vec2 appearMove{ 0, 0 };
    };

    struct BabyDuxParam
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

        [[TOML_BIND(Convene::Baby, "Convene.Baby")]]
        struct Convene
        {
            inline static s3d::Array<BabyDesc> Baby;
        };
    };
}