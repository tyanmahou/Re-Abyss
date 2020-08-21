#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Cycle::Splash
{
    struct Param
    {
        [[TOML_BIND_PARAM(Common::FadeTime, "Common.fadeTime")]]
        struct Common
        {
            inline static double FadeTime{ 3.0 };
        };
    };
}