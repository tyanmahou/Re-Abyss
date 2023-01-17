#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOML/TOMLBind.hpp>

namespace abyss::Actor::Enemy::Schield
{
    struct ShotParam
    {
        [[TOML_BIND(Base::Speed, "Base.speed")]]
        [[TOML_BIND(Base::ColRadius, "Base.colRadius")]]
        struct Base
        {
            inline static double Speed{ 420 };
            inline static double ColRadius{ 5 };
        };

        [[TOML_BIND(View::AnimeTimeSec, "View.animeTimeSec")]]
        [[TOML_BIND(View::RotateDeg, "View.rotateDeg")]]
        struct View
        {
            inline static double AnimeTimeSec{ 0.3 };
            inline static double RotateDeg{ 720.0 };
        };
    };
}