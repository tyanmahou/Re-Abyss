#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss::CodeZero
{
    struct HandParam
    {
        TOML_BIND_BEGIN;

        TOML_BIND_END;
    };
}