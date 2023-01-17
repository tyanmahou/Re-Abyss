#pragma once
#include <abyss/utils/TOML/TOMLBind.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::UI::BossHPBar
{
    struct Param
    {
        [[TOML_BIND(BrPos, "brPos")]]
        inline static s3d::Vec2 BrPos{ -310.0, -45.0 };
    };
}