#pragma once
#include <abyss/utils/TOML/TOMLBind.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::UI::PlayerInfo
{
    struct Param
    {
        [[TOML_BIND(Face::BasePos, "Face.basePos")]]
        [[TOML_BIND(Face::Size, "Face.size")]]
        struct Face
        {
            inline static s3d::Vec2 BasePos{ 80, 20 };
            inline static s3d::Vec2 Size{ 66, 66 };
        };
        [[TOML_BIND(HP::BasePos, "HP.basePos")]]
        [[TOML_BIND(HP::Offset, "HP.offset")]]
        struct HP
        {
            inline static s3d::Vec2 BasePos{ 80, 20 };
            inline static double Offset = 100.0;
        };
        [[TOML_BIND(Ooparts::BasePos, "Ooparts.basePos")]]
        [[TOML_BIND(Ooparts::NamePos, "Ooparts.namePos")]]
        struct Ooparts
        {
            inline static s3d::Vec2 BasePos{ 80, 20 };
            inline static s3d::Vec2 NamePos{ 80, 20 };
        };

        [[TOML_BIND(Main::DrawPos, "Main.drawPos")]]
        struct Main
        {
            inline static s3d::Vec2 DrawPos{ 80, 20 };
        };
    };
}
