#pragma once
#include <Siv3D/Triangle.hpp>
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    struct TentacleParam
    {
        [[TOML_BIND(Base::RotPivot, "Base.rotPivot")]]
        [[TOML_BIND(Base::Collider, "Base.collider")]]
        struct Base
        {
            inline static s3d::Vec2 RotPivot{};
            inline static s3d::Triangle Collider{};
        };
    };
}