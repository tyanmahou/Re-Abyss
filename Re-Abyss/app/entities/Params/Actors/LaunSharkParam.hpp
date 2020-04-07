#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
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
}