#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
#include <abyss/views/util/Pivot/PivotUtil.hpp>
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Rectangle.hpp>

namespace abyss::UI::SaveSelect
{
    struct Param
    {
        [[TOML_BIND(Horizon::Header, "Horizon.header")]]
        [[TOML_BIND(Horizon::Footer, "Horizon.footer")]]
        struct Horizon
        {
            inline static double Header{ -185.0 };
            inline static double Footer{ 230.0 };
        };

        [[TOML_BIND(SelectFrame::BasePos, "SelectFrame.basePos")]]
        [[TOML_BIND(SelectFrame::Size, "SelectFrame.size")]]
        [[TOML_BIND(SelectFrame::SelectSize, "SelectFrame.selectSize")]]
        [[TOML_BIND(SelectFrame::SelectCornerRate, "SelectFrame.selectCornerRate")]]
        [[TOML_BIND(SelectFrame::SelectPosOffset, "SelectFrame.selectPosOffset")]]
        [[TOML_BIND(SelectFrame::TrashSize, "SelectFrame.trashSize")]]
        struct SelectFrame
        {
            inline static s3d::Vec2 BasePos{ 480, 285 };
            inline static s3d::Vec2 Size{ 800, 350 };
            inline static s3d::Vec2 SelectSize{ 70, 56 };
            inline static s3d::Vec2 SelectCornerRate{ 0.8, 0.3 };
            inline static double SelectPosOffset{ 10 };
            inline static s3d::Vec2 TrashSize{ 60, 56 };
        };

        [[TOML_BIND(Confirm::BoardPos, "Confirm.boardPos")]]
        [[TOML_BIND(Confirm::BoardSize, "Confirm.boardSize")]]
        [[TOML_BIND(Confirm::MessagePos, "Confirm.messagePos")]]
        [[TOML_BIND(Confirm::ChoiceBasePos, "Confirm.choiceBasePos")]]
        [[TOML_BIND(Confirm::ChoiceOffset, "Confirm.choiceOffset")]]
        [[TOML_BIND(Confirm::CursorOffset, "Confirm.cursorOffset")]]
        [[TOML_BIND(Confirm::DetailPos, "Confirm.detailPos")]]
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
                return s3d::RectF{ PivotUtil::FromCenter(SelectFrame::BasePos) + BoardPos - BoardSize/2.0, BoardSize };
            }
        };
    };
}