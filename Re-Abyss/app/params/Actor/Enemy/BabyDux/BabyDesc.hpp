#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss::Actor::Enemy::BabyDux
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
}
