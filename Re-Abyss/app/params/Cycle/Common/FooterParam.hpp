#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Cycle
{
    struct FooterParam
    {
        [[TOML_BIND_PARAM(Tips::BasePos, "Tips.basePos")]]
        struct Tips
        {
            inline static s3d::Vec2 BasePos{ 900, 540 };
        };
    };
}