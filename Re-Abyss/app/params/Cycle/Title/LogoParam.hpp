#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Cycle::Title
{
    struct LogoParam
    {
        [[TOML_BIND_PARAM(Step::TimeSec, "Step.timeSec")]]
        [[TOML_BIND_PARAM(Step::BasePos, "Step.basePos")]]
        [[TOML_BIND_PARAM(Step::MoveOffset, "Step.moveOffset")]]
        [[TOML_BIND_PARAM(Step::MoveDiff, "Step.moveDiff")]]
        struct Step
        {
            inline static double TimeSec{ 0.166 };
            inline static s3d::Vec2 BasePos{ 480, 270 };
            inline static s3d::Vec2 MoveOffset{ 200, 200 };
            inline static s3d::Vec2 MoveDiff{ 100, 100 };
        };
        [[TOML_BIND_PARAM(End::Pos, "End.pos")]]
        struct End
        {
            inline static s3d::Vec2 Pos{ 480, 270 };
        };
    };
}