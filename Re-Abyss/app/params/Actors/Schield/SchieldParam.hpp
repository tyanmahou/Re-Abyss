#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss
{
    struct SchieldParam
    {
        TOML_BIND_BEGIN;

        [[TOML_BIND_PARAM(Base::Hp, "Base.hp")]]
        [[TOML_BIND_PARAM(Base::Size, "Base.size")]]
        struct Base
        {
            inline static s3d::int32 Hp{ 10 };
            inline static s3d::Vec2 Size{80, 60};
        };

        [[TOML_BIND_PARAM(Wait::TimeSec, "Wait.timeSec")]]
        [[TOML_BIND_PARAM(Wait::FaceColRadius, "Wait.faceColRadius")]]
        struct Wait
        {
            inline static double TimeSec{ 4.0 };
            inline static double FaceColRadius{ 15.0 };
        };

        [[TOML_BIND_PARAM(Attack::TimeSec, "Attack.timeSec")]]
        struct Attack
        {
            inline static double TimeSec{ 2.0 };
        };

        [[TOML_BIND_PARAM(View::AnimeTimeSec, "View.animeTimeSec")]]
        [[TOML_BIND_PARAM(View::TransitionTimeSec, "View.transitionTimeSec")]]
        struct View
        {
            inline static double AnimeTimeSec{ 1.0 };
            inline static double TransitionTimeSec{ 1.0 };
        };
        TOML_BIND_END;
    };
}