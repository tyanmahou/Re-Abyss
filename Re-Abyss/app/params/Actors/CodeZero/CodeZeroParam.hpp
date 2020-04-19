#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss
{
    struct CodeZeroParam
    {
        TOML_BIND_BEGIN;

        [[TOML_BIND_PARAM(Base::Hp, "Base.hp")]]
        struct Base
        {
            inline static s3d::int32 Hp{ 70 };
        };

        TOML_BIND_END;
    };
}