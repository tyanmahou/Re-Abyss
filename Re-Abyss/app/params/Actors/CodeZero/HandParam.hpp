#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss::CodeZero
{
    struct HandParam
    {
        TOML_BIND_BEGIN;

        [[TOML_BIND_PARAM(Base::ColRadius, "Base.colRadius")]]
        struct Base
        {
            inline static double ColRadius{ 35.0 };
        };

        [[TOML_BIND_PARAM(Setup::Speed, "Setup.speed")]]
        struct Setup
        {
            inline static double Speed{ 160.0 };
        };

        [[TOML_BIND_PARAM(Pursuit::Speed, "Pursuit.speed")]]
        struct Pursuit
        {
            inline static double Speed{ 180.0 };
        };

        [[TOML_BIND_PARAM(Attack::Speed, "Attack.speed")]]
        [[TOML_BIND_PARAM(Attack::WaitTimeSec, "Attack.waitTimeSec")]]
        struct Attack
        {
            inline static double Speed{ 850.0 };
            inline static double WaitTimeSec{ 0.5 };
        };
        TOML_BIND_END;
    };
}