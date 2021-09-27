#pragma once
#include <abyss/utils/TOMLBind/TOMLBindDef.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::UI::Title
{
    struct BgParam
    {
        [[TOML_BIND(Common::TimeSec, "Common.timeSec")]]
        struct Common
        {
            inline static s3d::Duration TimeSec{ 10.0 };
        };

        [[TOML_BIND(BackGround::EndPos, "BackGround.endPos")]]
        struct BackGround
        {
            inline static s3d::Vec2 EndPos{ 480, 170 };
        };
        [[TOML_BIND(Atlantis::StartPos, "Atlantis.startPos")]]
        struct Atlantis
        {
            inline static s3d::Vec2 StartPos{ 480, 710 };
        };
    };
}