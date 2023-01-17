#pragma once
#include <abyss/utils/TOML/TOMLBind.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Actor::Player
{
    struct CameraParam
    {
        [[TOML_BIND(MaxOffsetPos, "maxOffsetPos")]]
        inline static s3d::Vec2 MaxOffsetPos{ 40, 40 };

        [[TOML_BIND(StartSpeed, "startSpeed")]]
        inline static s3d::Vec2 StartSpeed{ 40, 40 };
        [[TOML_BIND(ErpRate, "erpRate")]]
        inline static double ErpRate{ 0.02 };
    };
}