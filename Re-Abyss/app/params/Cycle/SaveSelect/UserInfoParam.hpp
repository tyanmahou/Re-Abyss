#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Cycle::SaveSelect
{
    struct UserInfoParam
    {
        [[TOML_BIND(Common::BasePos, "Common.basePos")]]
        struct Common
        {
            inline static s3d::Vec2 BasePos{ 80, 120 };
        };

        [[TOML_BIND(HPBar::Pos, "HPBar.pos")]]
        struct HPBar
        {
            inline static s3d::Vec2 Pos{ 80, 120 };
        };

        [[TOML_BIND(Chapter::LabelPos, "Chapter.labelPos")]]
        [[TOML_BIND(Chapter::PosAt, "Chapter.posAt")]]
        [[TOML_BIND(Chapter::LinePos, "Chapter.linePos")]]
        [[TOML_BIND(Chapter::LineLength, "Chapter.lineLength")]]
        struct Chapter
        {
            inline static s3d::Vec2 LabelPos{ 80, 120 };
            inline static s3d::Vec2 PosAt{ 80, 120 };
            inline static s3d::Vec2 LinePos{ 80, 120 };
            inline static double LineLength = 100;
        };

        [[TOML_BIND(Player::Pos, "Player.pos")]]
        struct Player
        {
            inline static s3d::Vec2 Pos{ 80, 120 };
        };

        [[TOML_BIND(PlayMode::Pos, "PlayMode.pos")]]
        struct PlayMode
        {
            inline static s3d::Vec2 Pos{ 80, 120 };
        };

        [[TOML_BIND(PlayTime::LabelPos, "PlayTime.labelPos")]]
        [[TOML_BIND(PlayTime::Pos, "PlayTime.pos")]]
        struct PlayTime
        {
            inline static s3d::Vec2 LabelPos{ 80, 120 };
            inline static s3d::Vec2 Pos{ 80, 120 };
        };

        [[TOML_BIND(UpdatedAt::Pos, "UpdatedAt.pos")]]
        struct UpdatedAt
        {
            inline static s3d::Vec2 Pos{ 80, 120 };
        };

        [[TOML_BIND(OopartsList::Pos, "OopartsList.pos")]]
        [[TOML_BIND(OopartsList::OffsetX, "OopartsList.offsetX")]]
        struct OopartsList
        {
            inline static s3d::Vec2 Pos{ 80, 120 };
            inline static double OffsetX{10};
        };
    };
}