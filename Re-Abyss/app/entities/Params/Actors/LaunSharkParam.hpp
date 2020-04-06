#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TomlBind/TomlBind.hpp>
namespace abyss
{
    struct LaunSharkParam
    {
        struct
        {
            s3d::int32 hp;
            s3d::Vec2 size;
            double accelX;
        }base;

        struct
        {
            double maxSpeedX;
            double moveRangeY;
            double movePeriodSec;
            double attackRange;
            double launcherRange;

            double waitTimeSec;
            double onCollisionWaitTimeSec;
        }swim;

        struct
        {
            double attackTimeSec;
            double moveRangeY;
            double movePeriodSec;

            s3d::Vec2 size;
        }attack;
        struct
        {
            double attackTimeSec;
            double waitTimeSec;

        }launcher;
        struct
        {
            double swimAnimeTimeSec;
            double attackAnimeTimeSec;
        }view;
    };

    template<>
    struct TomlBind<LaunSharkParam>
    {
        LaunSharkParam operator()(const s3d::TOMLValue& toml)
        {
            LaunSharkParam ret;

            ret.base.hp = toml[U"Base.hp"].get<s3d::int32>();
            ret.base.size = toml[U"Base.size"].get<s3d::Vec2>();
            ret.base.accelX = toml[U"Base.accelX"].get<double>();

            ret.swim.maxSpeedX = toml[U"Swim.maxSpeedX"].get<double>();
            ret.swim.moveRangeY = toml[U"Swim.moveRangeY"].get<double>();
            ret.swim.movePeriodSec = toml[U"Swim.movePeriodSec"].get<double>();
            ret.swim.attackRange = toml[U"Swim.attackRange"].get<double>();
            ret.swim.launcherRange = toml[U"Swim.launcherRange"].get<double>();
            ret.swim.waitTimeSec = toml[U"Swim.waitTimeSec"].get<double>();
            ret.swim.onCollisionWaitTimeSec = toml[U"Swim.onCollisionWaitTimeSec"].get<double>();

            ret.attack.attackTimeSec = toml[U"Attack.attackTimeSec"].get<double>();
            ret.attack.moveRangeY = toml[U"Attack.moveRangeY"].get<double>();
            ret.attack.movePeriodSec = toml[U"Attack.movePeriodSec"].get<double>();
            ret.attack.size = toml[U"Attack.size"].get<s3d::Vec2>();

            ret.launcher.attackTimeSec = toml[U"Launcher.attackTimeSec"].get<double>();
            ret.launcher.waitTimeSec = toml[U"Launcher.waitTimeSec"].get<double>();

            ret.view.swimAnimeTimeSec = toml[U"View.swimAnimeTimeSec"].get<double>();
            ret.view.attackAnimeTimeSec = toml[U"View.attackAnimeTimeSec"].get<double>();
            return ret;
        }
    };
}