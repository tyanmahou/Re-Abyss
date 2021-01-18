#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Cycle::SaveSelect
{
    struct UserInfoParam
    {
        [[TOML_BIND_PARAM(Common::BasePos, "Common.basePos")]]
        struct Common
        {
            inline static s3d::Vec2 BasePos{ 80, 120 };
        };

        [[TOML_BIND_PARAM(HPBar::Pos, "HPBar.pos")]]
        struct HPBar
        {
            inline static s3d::Vec2 Pos{ 80, 120 };
        };

        [[TOML_BIND_PARAM(Player::Pos, "Player.pos")]]
        struct Player
        {
            inline static s3d::Vec2 Pos{ 80, 120 };
        };

        [[TOML_BIND_PARAM(PlayMode::Pos, "PlayMode.pos")]]
        struct PlayMode
        {
            inline static s3d::Vec2 Pos{ 80, 120 };
        };

        [[TOML_BIND_PARAM(PlayTime::LabelPos, "PlayTime.labelPos")]]
        [[TOML_BIND_PARAM(PlayTime::Pos, "PlayTime.pos")]]
        struct PlayTime
        {
            inline static s3d::Vec2 LabelPos{ 80, 120 };
            inline static s3d::Vec2 Pos{ 80, 120 };
        };

        [[TOML_BIND_PARAM(UpdatedAt::Pos, "UpdatedAt.pos")]]
        struct UpdatedAt
        {
            inline static s3d::Vec2 Pos{ 80, 120 };
        };

        [[TOML_BIND_PARAM(OopartsList::Pos, "OopartsList.pos")]]
        [[TOML_BIND_PARAM(OopartsList::OffsetX, "OopartsList.offsetX")]]
        struct OopartsList
        {
            inline static s3d::Vec2 Pos{ 80, 120 };
            inline static double OffsetX{10};
        };
    };
}