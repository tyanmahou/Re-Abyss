#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss::CaptainTako
{
    struct ShotParam
    {
        [[TOML_BIND_PARAM(Base::Speed, "Base.speed")]]
        [[TOML_BIND_PARAM(Base::ColRadius, "Base.colRadius")]]
        struct Base
        {
            inline static double Speed{ 420 };
            inline static double ColRadius{ 5.0 };
        };
    };
}