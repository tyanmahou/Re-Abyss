#pragma once
#include <abyss/utils/TOML/TOMLBind.hpp>

namespace abyss::Actor::Gimmick::ShutterWall
{
    struct Param
    {
        [[TOML_BIND(Hp, "hp")]]
        inline static s3d::int32 Hp{ 15 };

        [[TOML_BIND(ShutterTime, "shutterTime")]]
        inline static double ShutterTime{ 0.1 };

        [[TOML_BIND(ActionRange, "actionRange")]]
        inline static double ActionRange{ 300.0 };

        [[TOML_BIND(BaseSize, "baseSize")]]
        inline static s3d::Vec2 BaseSize{ 40, 160 };

        [[TOML_BIND(_quake, "Quake")]]
        struct Quake
        {
            [[TOML_BIND(Offset, "offset")]]
            inline static double Offset{ 4.0 };
            [[TOML_BIND(TimeSec, "timeSec")]]
            inline static double TimeSec{ 0.3 };
        };
    private:
        [[no_unique_address]] Quake _quake;
    };
}
