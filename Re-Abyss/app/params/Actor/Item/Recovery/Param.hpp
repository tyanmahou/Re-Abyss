#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOML/TOMLBind.hpp>

namespace abyss::Actor::Item::Recovery
{
    struct Setting
    {
        [[TOML_BIND(recoveryValue)]]
        s3d::int32 recoveryValue{ 1 };

        [[TOML_BIND(size)]]
        s3d::Vec2 size{ 40.0, 40.0 };

        [[TOML_BIND(coreOffset)]]
        s3d::Vec2 coreOffset{ 0.0, 0.0 };

        [[TOML_BIND(coreAnimTimeSec)]]
        double coreAnimTimeSec{ 0.5 };

        [[TOML_BIND(baseTopOffset)]]
        s3d::Vec2 baseTopOffset{ 0.0, 0.0 };

        [[TOML_BIND(baseBottomOffset)]]
        s3d::Vec2 baseBottomOffset{ 0.0, 0.0 };
    };

    struct Param
    {
        [[TOML_BIND(Shared::BaseAnimTimeSec, "Shared.baseAnimTimeSec")]]
        [[TOML_BIND(Shared::FrameAnimTimeSec, "Shared.frameAnimTimeSec")]]
        struct Shared
        {
            inline static double BaseAnimTimeSec{1.0};
            inline static double FrameAnimTimeSec{ 1.0 };
        };

        [[TOML_BIND(Small)]]
        inline static Setting Small;

        [[TOML_BIND(Middle)]]
        inline static Setting Middle;

        [[TOML_BIND(Big)]]
        inline static Setting Big;
    };
}