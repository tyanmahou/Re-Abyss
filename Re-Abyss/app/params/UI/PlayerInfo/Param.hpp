#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::ui::PlayerInfo
{
    struct Param
    {
        [[TOML_BIND_PARAM(Face::BasePos, "Face.basePos")]]
        struct Face
        {
            inline static s3d::Vec2 BasePos{ 80, 20 };
        };
        [[TOML_BIND_PARAM(HP::BasePos, "HP.basePos")]]
        [[TOML_BIND_PARAM(HP::Offset, "HP.offset")]]
        struct HP
        {
            inline static s3d::Vec2 BasePos{ 80, 20 };
            inline static double Offset = 100.0;
        };
        [[TOML_BIND_PARAM(Ooparts::BasePos, "Ooparts.basePos")]]
        [[TOML_BIND_PARAM(Ooparts::NamePos, "Ooparts.namePos")]]
        struct Ooparts
        {
            inline static s3d::Vec2 BasePos{ 80, 20 };
            inline static s3d::Vec2 NamePos{ 80, 20 };
        };

        [[TOML_BIND_PARAM(Main::DrawPos, "Main.drawPos")]]
        struct Main
        {
            inline static s3d::Vec2 DrawPos{ 80, 20 };
        };
    };
}