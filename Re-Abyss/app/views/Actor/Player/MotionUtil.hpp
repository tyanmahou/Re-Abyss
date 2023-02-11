#pragma once
#include <abyss/values/Forward.hpp>
#include <abyss/views/Actor/Player/Motion.hpp>

namespace abyss::Actor::Player
{
    class PlayerVM;

    class MotionUtil
    {
    public:
        static s3d::RectF StayRect(const PlayerVM* view);
        static s3d::RectF StayAtkRect(const PlayerVM* view);

        static s3d::RectF FloatRect(const PlayerVM* view);
        static s3d::RectF FloatAtkRect(const PlayerVM* view);

        static s3d::RectF RunRect(const PlayerVM* view);
        static s3d::RectF RunAtkRect(const PlayerVM* view);

        static s3d::RectF SwimRect(const PlayerVM* view);
        static s3d::RectF SwimAtkRect(const PlayerVM* view);

        static s3d::RectF DiveRect(const PlayerVM* view);
        static s3d::RectF DiveAtkRect(const PlayerVM* view);

        static s3d::RectF DamageRect(const PlayerVM* view);

        static s3d::RectF DeadRect(const PlayerVM* view, Vec2* outPos);

        static s3d::RectF LadderRect(const PlayerVM* view);
        static s3d::int32 LadderAtkPage(const PlayerVM* view);
        static s3d::RectF LadderAtkRect(const PlayerVM* view);

        static s3d::RectF LadderTopRect(const PlayerVM* view);
        static s3d::RectF LadderTopAtkRect(const PlayerVM* view);

        static s3d::RectF DoorRect(const PlayerVM* view);

        /// <summary>
        /// モーションによる攻撃手の座標取得
        /// </summary>
        /// <param name="motion"></param>
        /// <param name="forward"></param>
        /// <returns></returns>
        static s3d::Optional<s3d::Vec2> AtkHandPos(const PlayerVM* view);
    };
}
