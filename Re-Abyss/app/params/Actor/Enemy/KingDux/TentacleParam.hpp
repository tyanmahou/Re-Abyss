#pragma once
#include <Siv3D/Triangle.hpp>
#include <abyss/utils/TOML/TOMLBindDef.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/Kind.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    struct TentacleDesc
    {
        [[TOML_BIND(offset)]]
        s3d::Vec2 offset{ 0, 0 };
        [[TOML_BIND(rotateDeg)]]
        double rotateDeg = 0;
        [[TOML_BIND(distOffset)]]
        double distOffset{};
        [[TOML_BIND(kind)]]
        Tentacle::Kind kind = Tentacle::Kind::PursuitStab;
        [[TOML_BIND(waitTimeSec)]]
        double waitTimeSec = 0;
    };

    struct TentacleParam
    {
        [[TOML_BIND(Base::RotPivot, "Base.rotPivot")]]
        [[TOML_BIND(Base::Collider, "Base.collider")]]
        struct Base
        {
            inline static s3d::Vec2 RotPivot{};
            inline static s3d::Triangle Collider{};
        };

        [[TOML_BIND(Appear::Speed, "Appear.speed")]]
        [[TOML_BIND(Appear::MoveTimeSec, "Appear.moveTimeSec")]]
        struct Appear
        {
            inline static double Speed{ 80.0 };
            inline static double MoveTimeSec{ 1.5 };
        };

        [[TOML_BIND(Stab::Tentacle, "Stab.Tentacle")]]
        [[TOML_BIND(Stab::Tentacle2, "Stab.Tentacle2")]]
        [[TOML_BIND(Stab::Tentacle3, "Stab.Tentacle3")]]
        struct Stab
        {
            inline static s3d::Array<TentacleDesc> Tentacle{};
            inline static s3d::Array<TentacleDesc> Tentacle2{};
            inline static s3d::Array<TentacleDesc> Tentacle3{};
        };

        [[TOML_BIND(PursuitStab::Tentacle, "PursuitStab.Tentacle")]]
        struct PursuitStab
        {
            inline static s3d::Array<TentacleDesc> Tentacle{};
        };
    };
}