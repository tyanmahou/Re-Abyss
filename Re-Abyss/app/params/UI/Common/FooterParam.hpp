#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::UI
{
    struct FooterParam
    {
        [[TOML_BIND(Tips::BasePos, "Tips.basePos")]]
        struct Tips
        {
            inline static s3d::Vec2 BasePos{ 900, 540 };
        };
    };
}