#include <abyss/components/Actor/Enemy/BazookaKun/TargetCtrl.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/params/Actor/Enemy/BazookaKun/Param.hpp>

namespace abyss::Actor::Enemy::BazookaKun
{
    TargetCtrl::TargetCtrl(ActorObj* pActor):
        m_pActor(pActor),
        m_waitTimer(2.0)
    {
    }

    void TargetCtrl::onStart()
    {
        m_body = m_pActor->find<Body>();
    }

    void TargetCtrl::onLastUpdate()
    {
        auto dt = m_pActor->deltaTime();
        const auto& pos = m_body->getPos();
        // 基準点の計算
        RectF rect{ pos - Param::Base::Size / 2, Param::Base::Size };
        auto center = rect.center();
        auto pivot = center + Vec2{ m_isMirrored ? 3 : -3, m_isFlipped ? -15 : 15 };
        pivot = pivot.rotateAt(rect.bl(), s3d::ToRadians(m_rotate));
        const auto& playerPos = ActorUtils::PlayerPos(*m_pActor);

        auto eyeVec = Vec2{ m_isMirrored ? 1 : -1, 0 }.rotated(s3d::ToRadians(m_rotate));

        // 角度の計算
        auto toPlayer = playerPos - pivot;
        if (
            m_isValidAim &&
            !toPlayer.isZero() &&
            toPlayer.normalized().dot(eyeVec) > Cos(s3d::ToRadians(90))
        ) {
            double targetRad = 0;
            targetRad = toPlayer.getAngle();
            // 0 ～ 360度にする
            auto targetRotate = s3d::Math::ToDegrees(targetRad) + 90 - m_rotate + (m_isMirrored ? 180 : 0);

            // 角度の近いほうに調整
            if (Abs(targetRotate - m_bazookaRotate) > Abs((targetRotate - 360) - m_bazookaRotate)) {
                targetRotate -= 360;
            }
            if (Abs(targetRotate - m_bazookaRotate) > Abs((targetRotate + 360) - m_bazookaRotate)) {
                targetRotate += 360;
            }
            m_bazookaRotateTarget = targetRotate;

            m_waitTimer.reset();
        } else {
            // 一定時間たったら戻る
            m_waitTimer.update(dt);
            if (m_waitTimer.isEnd()) {
                m_bazookaRotateTarget = 0;
            }
        }
        // 補完
        auto deltaRot = 40.0 * dt;
        if (m_bazookaRotateTarget > m_bazookaRotate + deltaRot) {
            m_bazookaRotate += deltaRot;
        } else if (m_bazookaRotateTarget < m_bazookaRotate - deltaRot) {
            m_bazookaRotate -= deltaRot;
        } else {
            m_bazookaRotate = m_bazookaRotateTarget;
        }

        // Clamp
        if (m_isMirrored != m_isFlipped) {
            m_bazookaRotate = Clamp(m_bazookaRotate, -60.0, 0.0);
        } else {
            m_bazookaRotate = Clamp(m_bazookaRotate, 0.0, 60.0);
        }
    }
}
