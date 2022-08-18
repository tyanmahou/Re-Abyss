#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Actor::Enemy::BazookaKun
{
    struct Param
    {
        [[TOML_BIND(Base::Hp, "Base.hp")]]
        [[TOML_BIND(Base::Size, "Base.size")]]
        [[TOML_BIND(Base::BodySize, "Base.bodySize")]]
        struct Base
        {
            inline static s3d::int32 Hp{ 6 };
            inline static s3d::Vec2 Size{ 90, 60 };
            inline static s3d::Vec2 BodySize{90, 60};
        };
    };
}
