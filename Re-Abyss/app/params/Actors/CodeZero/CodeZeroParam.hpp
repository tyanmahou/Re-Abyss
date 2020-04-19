#pragma once
#include <Siv3D/Vector2D.hpp>
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

        [[TOML_BIND_PARAM(Head::ColRadius, "Head.colRadius")]]
        [[TOML_BIND_PARAM(Head::Offset, "Head.offset")]]
        struct Head
        {
            inline static double ColRadius{ 35.0 };
            inline static s3d::Vec2 Offset{ 0, -50 };
        };

        TOML_BIND_END;
    };
}