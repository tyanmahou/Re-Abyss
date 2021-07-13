#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss::Actor::Enemy::CaptainTako
{
    struct ShotParam
    {
        [[TOML_BIND(Base::Speed, "Base.speed")]]
        [[TOML_BIND(Base::ColRadius, "Base.colRadius")]]
        struct Base
        {
            inline static double Speed{ 420 };
            inline static double ColRadius{ 5.0 };
        };
    };
}