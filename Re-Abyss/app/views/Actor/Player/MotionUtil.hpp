#pragma once
#include <abyss/values/Forward.hpp>
#include <abyss/views/Actor/Player/Motion.hpp>

namespace abyss::Actor::Player
{
    class MotionUtil
    {
    public:
        /// <summary>
        /// モーションによる攻撃手の座標取得
        /// </summary>
        /// <param name="motion"></param>
        /// <param name="forward"></param>
        /// <returns></returns>
        static s3d::Optional<s3d::Vec2> AtkHandPos(Motion motion, Forward forward, const s3d::Vec2& pos);
    };
}
