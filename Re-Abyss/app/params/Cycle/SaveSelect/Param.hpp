#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Cycle::SaveSelect
{
    struct Param
    {
        [[TOML_BIND_PARAM(Horizon::Header, "Horizon.header")]]
        [[TOML_BIND_PARAM(Horizon::Footer, "Horizon.footer")]]
        struct Horizon
        {
            inline static double Header{ 0.0 };
            inline static double Footer{ 0.0 };
        };
    };
}