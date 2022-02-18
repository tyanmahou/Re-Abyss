#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    struct HandParam
    {
        [[TOML_BIND(Base::InitOffs, "Base.initOffs")]]
        [[TOML_BIND(Base::ColRadius, "Base.colRadius")]]
        [[TOML_BIND(Base::HorizontalDist, "Base.horizontalDist")]]
        [[TOML_BIND(Base::VerticalDist, "Base.verticalDist")]]
        struct Base
        {
            inline static s3d::Vec2 InitOffs{};
            inline static double ColRadius{ 35.0 };
            inline static double HorizontalDist{ 400.0 };
            inline static double VerticalDist{ 250.0 };
        };

        [[TOML_BIND(Setup::Speed, "Setup.speed")]]
        struct Setup
        {
            inline static double Speed{ 160.0 };
        };

        [[TOML_BIND(Pursuit::Speed, "Pursuit.speed")]]
        struct Pursuit
        {
            inline static double Speed{ 180.0 };
        };

        [[TOML_BIND(Attack::Speed, "Attack.speed")]]
        [[TOML_BIND(Attack::WaitTimeSec, "Attack.waitTimeSec")]]
        struct Attack
        {
            inline static double Speed{ 850.0 };
            inline static double WaitTimeSec{ 0.5 };
        };
    };
}