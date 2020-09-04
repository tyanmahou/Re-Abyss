#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss::Actor::Player
{
    struct ShotParam
    {
        [[TOML_BIND_PARAM(Base::Speed, "Base.speed")]]
        struct Base
        {
            inline static double Speed{ 840 };
        };

        [[TOML_BIND_PARAM(Normal::Radius, "Normal.radius")]]
        [[TOML_BIND_PARAM(Normal::Power, "Normal.power")]]
        struct Normal
        {
            inline static double Radius{ 5 };
            inline static s3d::int32 Power{ 2 };
        };

        [[TOML_BIND_PARAM(Small::Charge, "Small.charge")]]
        [[TOML_BIND_PARAM(Small::Radius, "Small.radius")]]
        [[TOML_BIND_PARAM(Small::Power, "Small.power")]]
        struct Small
        {
            inline static double Charge{ 10 };
            inline static double Radius{ 8 };
            inline static s3d::int32 Power{ 3 };
        };

        [[TOML_BIND_PARAM(Medium::Charge, "Medium.charge")]]
        [[TOML_BIND_PARAM(Medium::Radius, "Medium.radius")]]
        [[TOML_BIND_PARAM(Medium::Power, "Medium.power")]]
        struct Medium
        {
            inline static double Charge{ 60 };
            inline static double Radius{ 16 };
            inline static s3d::int32 Power{ 6 };
        };

        [[TOML_BIND_PARAM(Big::Charge, "Big.charge")]]
        [[TOML_BIND_PARAM(Big::Radius, "Big.radius")]]
        [[TOML_BIND_PARAM(Big::Power, "Big.power")]]
        struct Big
        {
            inline static double Charge{ 120 };
            inline static double Radius{ 24 };
            inline static s3d::int32 Power{ 12 };
        };
    };
}