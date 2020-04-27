#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss::Schield
{
    struct ShotParam
    {
        [[TOML_BIND_PARAM(Base::Speed, "Base.speed")]]
        [[TOML_BIND_PARAM(Base::ColRadius, "Base.colRadius")]]
        struct Base
        {
            inline static double Speed{ 420 };
            inline static double ColRadius{ 5 };
        };

        [[TOML_BIND_PARAM(View::AnimeTimeSec, "View.animeTimeSec")]]
        [[TOML_BIND_PARAM(View::RotateDeg, "View.rotateDeg")]]
        struct View
        {
            inline static double AnimeTimeSec{ 0.3 };
            inline static double RotateDeg{ 720.0 };
        };
    };
}