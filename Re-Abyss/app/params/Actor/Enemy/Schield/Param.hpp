#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss::Actor::Enemy::Schield
{
    struct Param
    {
        [[TOML_BIND(Base::Hp, "Base.hp")]]
        [[TOML_BIND(Base::Size, "Base.size")]]
        struct Base
        {
            inline static s3d::int32 Hp{ 10 };
            inline static s3d::Vec2 Size{80, 60};
        };

        [[TOML_BIND(Wait::TimeSec, "Wait.timeSec")]]
        [[TOML_BIND(Wait::FaceColRadius, "Wait.faceColRadius")]]
        struct Wait
        {
            inline static double TimeSec{ 4.0 };
            inline static double FaceColRadius{ 15.0 };
        };

        [[TOML_BIND(Attack::TimeSec, "Attack.timeSec")]]
        struct Attack
        {
            inline static double TimeSec{ 2.0 };
        };

        [[TOML_BIND(View::AnimeTimeSec, "View.animeTimeSec")]]
        [[TOML_BIND(View::TransitionTimeSec, "View.transitionTimeSec")]]
        struct View
        {
            inline static double AnimeTimeSec{ 1.0 };
            inline static double TransitionTimeSec{ 1.0 };
        };
    };
}