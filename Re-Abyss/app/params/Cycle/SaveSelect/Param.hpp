#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Rectangle.hpp>

namespace abyss::Cycle::SaveSelect
{
    struct Param
    {
        [[TOML_BIND_PARAM(Horizon::Header, "Horizon.header")]]
        [[TOML_BIND_PARAM(Horizon::Footer, "Horizon.footer")]]
        struct Horizon
        {
            inline static double Header{ -185.0 };
            inline static double Footer{ 230.0 };
        };

        [[TOML_BIND_PARAM(SelectFrame::BasePos, "SelectFrame.basePos")]]
        [[TOML_BIND_PARAM(SelectFrame::Size, "SelectFrame.size")]]
        [[TOML_BIND_PARAM(SelectFrame::SelectSize, "SelectFrame.selectSize")]]
        [[TOML_BIND_PARAM(SelectFrame::SelectCornerRate, "SelectFrame.selectCornerRate")]]
        [[TOML_BIND_PARAM(SelectFrame::SelectPosOffset, "SelectFrame.selectPosOffset")]]
        [[TOML_BIND_PARAM(SelectFrame::TrashSize, "SelectFrame.trashSize")]]
        struct SelectFrame
        {
            inline static s3d::Vec2 BasePos{ 480, 285 };
            inline static s3d::Vec2 Size{ 800, 350 };
            inline static s3d::Vec2 SelectSize{ 70, 56 };
            inline static s3d::Vec2 SelectCornerRate{ 0.8, 0.3 };
            inline static double SelectPosOffset{ 10 };
            inline static s3d::Vec2 TrashSize{ 60, 56 };
        };

        [[TOML_BIND_PARAM(Confirm::BoardPos, "Confirm.boardPos")]]
        [[TOML_BIND_PARAM(Confirm::BoardSize, "Confirm.boardSize")]]
        [[TOML_BIND_PARAM(Confirm::MessagePos, "Confirm.messagePos")]]
        [[TOML_BIND_PARAM(Confirm::ChoiceBasePos, "Confirm.choiceBasePos")]]
        [[TOML_BIND_PARAM(Confirm::ChoiceOffset, "Confirm.choiceOffset")]]
        [[TOML_BIND_PARAM(Confirm::CursorOffset, "Confirm.cursorOffset")]]
        [[TOML_BIND_PARAM(Confirm::DetailPos, "Confirm.detailPos")]]
        struct Confirm
        {
            inline static s3d::Vec2 BoardPos{ 480, 320 };
            inline static s3d::Vec2 BoardSize{ 500, 270 };
            inline static s3d::Vec2 MessagePos{ 480, 220 };
            inline static s3d::Vec2 ChoiceBasePos{ 480, 290 };
            inline static double ChoiceOffset = 40.0;
            inline static double CursorOffset = -100.0;
            inline static s3d::Vec2 DetailPos{ 480, 285 };

            inline static s3d::RectF Board()
            {
                return s3d::RectF{ BoardPos - BoardSize/2.0, BoardSize };
            }
        };
    };
}