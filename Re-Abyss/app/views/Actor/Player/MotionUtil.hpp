#pragma once
#include <abyss/values/Forward.hpp>
#include <abyss/views/Actor/Player/Motion.hpp>

namespace abyss::Actor::Player
{
    class PlayerVM;

    class MotionUtil
    {
    public:
        static s3d::int32 LadderAtkPage(const PlayerVM* view);
        static s3d::RectF LadderAtkRect(const PlayerVM* view);

        /// <summary>
        /// モーションによる攻撃手の座標取得
        /// </summary>
        /// <param name="motion"></param>
        /// <param name="forward"></param>
        /// <returns></returns>
        static s3d::Optional<s3d::Vec2> AtkHandPos(const PlayerVM* view);
    };
}
