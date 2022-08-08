#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss::Actor::Enemy::BazookaKun
{
    struct Param
    {
        [[TOML_BIND(Base::Hp, "Base.hp")]]
        struct Base
        {
            inline static s3d::int32 Hp{ 6 };
        };
    };
}
