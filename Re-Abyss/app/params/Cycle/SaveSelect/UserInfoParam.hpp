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

        [[TOML_BIND_PARAM(PlayTime::Pos, "PlayTime.pos")]]
        struct PlayTime
        {
            inline static s3d::Vec2 Pos{ 80, 120 };
        };

        [[TOML_BIND_PARAM(UpdatedAt::Pos, "UpdatedAt.pos")]]
        struct UpdatedAt
        {
            inline static s3d::Vec2 Pos{ 80, 120 };
        };
    };
}