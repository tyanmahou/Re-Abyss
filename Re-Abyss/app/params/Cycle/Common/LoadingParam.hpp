#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Cycle
{
    struct LoadingParam
    {
        [[TOML_BIND_PARAM(Slime::BasePos, "Slime.basePos")]]
        struct Slime
        {
            inline static s3d::Vec2 BasePos{ 900, 540 };
        };

        [[TOML_BIND_PARAM(Text::BasePos, "Text.basePos")]]
        [[TOML_BIND_PARAM(Text::OffsetX, "Text.offsetX")]]
        struct Text
        {
            inline static s3d::Vec2 BasePos{ 900, 540 };
            inline static double OffsetX{ 5.0 };
        };
    };
}