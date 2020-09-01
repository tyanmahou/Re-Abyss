#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Cycle::Title
{
    struct BgParam
    {
        [[TOML_BIND_PARAM(Common::TimeSec, "Common.timeSec")]]
        struct Common
        {
            inline static double TimeSec{ 10.0 };
        };

        [[TOML_BIND_PARAM(BackGround::EndPos, "BackGround.endPos")]]
        struct BackGround
        {
            inline static s3d::Vec2 EndPos{ 480, 170 };
        };
        [[TOML_BIND_PARAM(Atlantis::StartPos, "Atlantis.startPos")]]
        struct Atlantis
        {
            inline static s3d::Vec2 StartPos{ 480, 710 };
        };
    };
}