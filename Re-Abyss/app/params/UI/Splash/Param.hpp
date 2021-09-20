#pragma once
#include <abyss/utils/TOMLBind/TOMLBindDef.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::UI::Splash
{
    struct Param
    {
        [[TOML_BIND(Common::FadeTime, "Common.fadeTime")]]
        struct Common
        {
            inline static s3d::Duration FadeTime{ 3.0 };
        };
    };
}