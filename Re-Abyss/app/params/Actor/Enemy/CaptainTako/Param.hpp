#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOML/TOMLBind.hpp>

namespace abyss::Actor::Enemy::CaptainTako
{
    struct Param
    {
        [[TOML_BIND(Base::Hp, "Base.hp")]]
        [[TOML_BIND(Base::Size, "Base.size")]]
        [[TOML_BIND(Base::Pivot, "Base.pivot")]]
        struct Base
        {
            inline static s3d::int32 Hp{ 10 };
            inline static s3d::Vec2 Size{ 32, 38 };
            inline static s3d::Vec2 Pivot{ 0, 1 };
        };

        [[TOML_BIND(Wait::TimeSec, "Wait.timeSec")]]
        struct Wait
        {
            inline static double TimeSec{ 2.0 };
        };

        [[TOML_BIND(Charge::TimeSec, "Charge.timeSec")]]
        struct Charge
        {
            inline static double TimeSec{ 2.0 };
        };

        [[TOML_BIND(Attack::IntervalTimeSec, "Attack.intervalTimeSec")]]
        [[TOML_BIND(Attack::AttackCount, "Attack.attackCount")]]
        struct Attack
        {
            inline static double IntervalTimeSec{ 0.1 };
            inline static s3d::int32 AttackCount{ 3 };
        };

        [[TOML_BIND(View::AnimeTimeSec, "View.animeTimeSec")]]
        [[TOML_BIND(View::ChargingAddScale, "View.chargingAddScale")]]
        struct View
        {
            inline static double AnimeTimeSec{ 1.0 };
            inline static double ChargingAddScale{ 0.4 };
        };
    };
}