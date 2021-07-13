#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
namespace abyss::Actor::Enemy::LaunShark
{
    struct Param
    {
        [[TOML_BIND(Base::Hp, "Base.hp")]]
        [[TOML_BIND(Base::Size, "Base.size")]]
        [[TOML_BIND(Base::AccelX, "Base.accelX")]]
        struct Base
        {
            inline static s3d::int32 Hp{ 10 };
            inline static s3d::Vec2 Size{ 120, 40 };
            inline static double AccelX{ 360 };
        };

        [[TOML_BIND(Swim::MaxSpeedX, "Swim.maxSpeedX")]]
        [[TOML_BIND(Swim::MoveRangeY, "Swim.moveRangeY")]]
        [[TOML_BIND(Swim::MovePeriodSec, "Swim.movePeriodSec")]]
        [[TOML_BIND(Swim::AttackRange, "Swim.attackRange")]]
        [[TOML_BIND(Swim::LauncherRange, "Swim.launcherRange")]]
        [[TOML_BIND(Swim::WaitTimeSec, "Swim.waitTimeSec")]]
        [[TOML_BIND(Swim::OnCollisionWaitTimeSec, "Swim.onCollisionWaitTimeSec")]]
        struct Swim
        {
            inline static double MaxSpeedX{ 180 };
            inline static double MoveRangeY{ 20 };
            inline static double MovePeriodSec{ 6.0 };
            inline static double AttackRange{ 200 };
            inline static double LauncherRange{ 500 };

            inline static double WaitTimeSec{ 1.5 };
            inline static double OnCollisionWaitTimeSec{ 0.5 };
        };

        [[TOML_BIND(Attack::AttackTimeSec, "Attack.attackTimeSec")]]
        [[TOML_BIND(Attack::MoveRangeY, "Attack.moveRangeY")]]
        [[TOML_BIND(Attack::MovePeriodSec, "Attack.movePeriodSec")]]
        [[TOML_BIND(Attack::Size, "Attack.size")]]
        struct Attack
        {
            inline static double AttackTimeSec{ 4.0 };
            inline static double MoveRangeY{ 40.0 };
            inline static double MovePeriodSec{ 3.0 };

            inline static s3d::Vec2 Size{120, 60};
        };

        [[TOML_BIND(Launcher::AttackTimeSec, "Launcher.attackTimeSec")]]
        [[TOML_BIND(Launcher::WaitTimeSec, "Launcher.waitTimeSec")]]
        struct Launcher
        {
            inline static double AttackTimeSec{1.2};
            inline static double WaitTimeSec{0.8};
        };

        [[TOML_BIND(View::SwimAnimeTimeSec, "View.swimAnimeTimeSec")]]
        [[TOML_BIND(View::AttackAnimeTimeSec, "View.attackAnimeTimeSec")]]
        struct View
        {
            inline static double SwimAnimeTimeSec{1.0};
            inline static double AttackAnimeTimeSec{0.8};
        };
    };
}