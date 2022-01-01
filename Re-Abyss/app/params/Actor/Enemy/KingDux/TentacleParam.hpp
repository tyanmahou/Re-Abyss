#pragma once
#include <Siv3D/Triangle.hpp>
#include <abyss/utils/TOMLBind/TOMLBindDef.hpp>
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

        [[TOML_BIND(Stab::Tentacle1, "Stab.Tentacle1")]]
        [[TOML_BIND(Stab::Tentacle2, "Stab.Tentacle2")]]
        struct Stab
        {
            inline static TentacleDesc Tentacle1{};
            inline static TentacleDesc Tentacle2{};
        };

        [[TOML_BIND(PursuitStab::Tentacle1, "PursuitStab.Tentacle1")]]
        [[TOML_BIND(PursuitStab::Tentacle2, "PursuitStab.Tentacle2")]]
        struct PursuitStab
        {
            inline static TentacleDesc Tentacle1{};
            inline static TentacleDesc Tentacle2{};
        };
    };
}