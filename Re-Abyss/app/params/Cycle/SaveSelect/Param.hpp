#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Cycle::SaveSelect
{
    struct Param
    {
        [[TOML_BIND_PARAM(Horizon::Header, "Horizon.header")]]
        [[TOML_BIND_PARAM(Horizon::Footer, "Horizon.footer")]]
        struct Horizon
        {
            inline static double Header{ 0.0 };
            inline static double Footer{ 0.0 };
        };

        [[TOML_BIND_PARAM(SelectFrame::BasePos, "SelectFrame.basePos")]]
        [[TOML_BIND_PARAM(SelectFrame::Size, "SelectFrame.size")]]
        [[TOML_BIND_PARAM(SelectFrame::SelectSize, "SelectFrame.selectSize")]]
        [[TOML_BIND_PARAM(SelectFrame::SelectCornerRate, "SelectFrame.selectCornerRate")]]
        [[TOML_BIND_PARAM(SelectFrame::SelectPosOffset, "SelectFrame.selectPosOffset")]]
        [[TOML_BIND_PARAM(SelectFrame::TrashSize, "SelectFrame.trashSize")]]
        struct SelectFrame
        {
            inline static s3d::Vec2 BasePos{ 480, 260 };
            inline static s3d::Vec2 Size{ 800, 300 };
            inline static s3d::Vec2 SelectSize{ 50, 50 };
            inline static s3d::Vec2 SelectCornerRate{ 0.3, 0.3 };
            inline static double SelectPosOffset{ 10 };
            inline static s3d::Vec2 TrashSize{ 50, 50 };
        };
    };
}