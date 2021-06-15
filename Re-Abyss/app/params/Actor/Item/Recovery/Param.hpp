#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss::Actor::Item::Recovery
{
    struct Setting
    {
        [[TOML_BIND_PARAM(recoveryValue)]]
        s3d::int32 recoveryValue{ 1 };

        [[TOML_BIND_PARAM(size)]]
        s3d::Vec2 size{ 40.0, 40.0 };

        [[TOML_BIND_PARAM(coreOffset)]]
        s3d::Vec2 coreOffset{ 0.0, 0.0 };

        [[TOML_BIND_PARAM(coreAnimTimeSec)]]
        double coreAnimTimeSec{ 0.5 };

        [[TOML_BIND_PARAM(baseTopOffset)]]
        s3d::Vec2 baseTopOffset{ 0.0, 0.0 };

        [[TOML_BIND_PARAM(baseBottomOffset)]]
        s3d::Vec2 baseBottomOffset{ 0.0, 0.0 };
    };

    struct Param
    {
        [[TOML_BIND_PARAM(Shared::BaseAnimTimeSec, "Shared.baseAnimTimeSec")]]
        [[TOML_BIND_PARAM(Shared::FrameAnimTimeSec, "Shared.frameAnimTimeSec")]]
        struct Shared
        {
            inline static double BaseAnimTimeSec{1.0};
            inline static double FrameAnimTimeSec{ 1.0 };
        };

        [[TOML_BIND_PARAM(Small)]]
        inline static Setting Small;

        [[TOML_BIND_PARAM(Small)]]
        inline static Setting Middle;

        [[TOML_BIND_PARAM(Big)]]
        inline static Setting Big;
    };
}