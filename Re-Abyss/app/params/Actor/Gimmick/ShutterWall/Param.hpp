#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss::Actor::Gimmick::ShutterWall
{
    struct Param
    {
        [[TOML_BIND(Hp, "hp")]]
        inline static s3d::int32 Hp{ 15 };

        [[TOML_BIND(BaseSize, "baseSize")]]
        inline static s3d::Vec2 BaseSize{ 40, 160 };
    };
}
