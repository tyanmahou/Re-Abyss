#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss::Actor::Player
{
    struct ShotParam
    {
        [[TOML_BIND(Base::Speed, "Base.speed")]]
        [[TOML_BIND(Base::ColliderRate, "Base.colliderRate")]]
        struct Base
        {
            inline static double Speed{ 840 };
            inline static double ColliderRate{ 1.3 };
        };

        [[TOML_BIND(Normal::Radius, "Normal.radius")]]
        [[TOML_BIND(Normal::Power, "Normal.power")]]
        struct Normal
        {
            inline static double Radius{ 5 };
            inline static s3d::int32 Power{ 2 };
        };

        [[TOML_BIND(Small::Charge, "Small.charge")]]
        [[TOML_BIND(Small::Radius, "Small.radius")]]
        [[TOML_BIND(Small::Power, "Small.power")]]
        struct Small
        {
            inline static double Charge{ 10 };
            inline static double Radius{ 8 };
            inline static s3d::int32 Power{ 3 };
        };

        [[TOML_BIND(Medium::Charge, "Medium.charge")]]
        [[TOML_BIND(Medium::Radius, "Medium.radius")]]
        [[TOML_BIND(Medium::Power, "Medium.power")]]
        struct Medium
        {
            inline static double Charge{ 60 };
            inline static double Radius{ 16 };
            inline static s3d::int32 Power{ 6 };
        };

        [[TOML_BIND(Big::Charge, "Big.charge")]]
        [[TOML_BIND(Big::Radius, "Big.radius")]]
        [[TOML_BIND(Big::Power, "Big.power")]]
        struct Big
        {
            inline static double Charge{ 120 };
            inline static double Radius{ 24 };
            inline static s3d::int32 Power{ 12 };
        };
    };
}