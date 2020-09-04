#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss::Actor::Enemy::Slime
{
    struct Param
    {
        [[TOML_BIND_PARAM(Base::Hp, "Base.hp")]]
        struct Base
        {
            inline static s3d::int32 Hp{ 6 };
        };

        [[TOML_BIND_PARAM(Walk::Size, "Walk.size")]]
        [[TOML_BIND_PARAM(Walk::Pivot, "Walk.pivot")]]
        [[TOML_BIND_PARAM(Walk::AccelX, "Walk.accelX")]]
        [[TOML_BIND_PARAM(Walk::MaxSpeedX, "Walk.maxSpeedX")]]
        [[TOML_BIND_PARAM(Walk::SearchRange, "Walk.searchRange")]]
        struct Walk
        {
            inline static s3d::Vec2 Size{ 35, 25 };
            inline static s3d::Vec2 Pivot{ 0, 7.5 };
            inline static double AccelX{ 720 };
            inline static double MaxSpeedX{ 60 };
            inline static double SearchRange{ 200 };
        };

        [[TOML_BIND_PARAM(Jump::Size, "Jump.size")]]
        [[TOML_BIND_PARAM(Jump::JumpHeight, "Jump.jumpHeight")]]
        struct Jump
        {
            inline static s3d::Vec2 Size{ 32, 32 };
            inline static double JumpHeight{ 80 };
        };

        [[TOML_BIND_PARAM(View::WalkAnimeTimeSec, "View.walkAnimeTimeSec")]]
        struct View
        {
            inline static double WalkAnimeTimeSec{ 1.0 };
        };
    };
}