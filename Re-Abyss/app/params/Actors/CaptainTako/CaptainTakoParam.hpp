#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss
{
    struct CaptainTakoParam
    {
        TOML_BIND_BEGIN;

        [[TOML_BIND_PARAM(Base::Hp, "Base.hp")]]
        [[TOML_BIND_PARAM(Base::Size, "Base.size")]]
        [[TOML_BIND_PARAM(Base::Pivot, "Base.pivot")]]
        struct Base
        {
            inline static s3d::int32 Hp{ 10 };
            inline static s3d::Vec2 Size{ 32, 38 };
            inline static s3d::Vec2 Pivot{ 0, 1 };
        };

        [[TOML_BIND_PARAM(Wait::TimeSec, "Wait.timeSec")]]
        struct Wait
        {
            inline static double TimeSec{ 2.0 };
        };

        [[TOML_BIND_PARAM(Charge::TimeSec, "Charge.timeSec")]]
        struct Charge
        {
            inline static double TimeSec{ 2.0 };
        };

        [[TOML_BIND_PARAM(Attack::IntervalTimeSec, "Attack.intervalTimeSec")]]
        [[TOML_BIND_PARAM(Attack::AttackCount, "Attack.attackCount")]]
        struct Attack
        {
            inline static double IntervalTimeSec{ 0.1 };
            inline static s3d::int32 AttackCount{ 3 };
        };

        [[TOML_BIND_PARAM(View::AnimeTimeSec, "View.animeTimeSec")]]
        [[TOML_BIND_PARAM(View::ChargingAddScale, "View.chargingAddScale")]]
        struct View
        {
            inline static double AnimeTimeSec{ 1.0 };
            inline static double ChargingAddScale{ 0.4 };
        };

        TOML_BIND_END;
    };
}