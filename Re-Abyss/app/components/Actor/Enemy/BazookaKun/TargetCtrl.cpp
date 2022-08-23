#include <abyss/components/Actor/Enemy/BazookaKun/TargetCtrl.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/params/Actor/Enemy/BazookaKun/Param.hpp>
#include <abyss/utils/Interp/InterpUtil.hpp>
#include <abyss/utils/Axis2/Axis2.hpp>
#include <abyss/utils/Math/Math.hpp>

namespace abyss::Actor::Enemy::BazookaKun
{
    TargetCtrl::TargetCtrl(ActorObj* pActor):
        m_pActor(pActor),
        m_waitTimer(2.0)
    {
    }

    TargetCtrl& TargetCtrl::setBazookaRotate(double rotate)
    {
        m_bazookaRotate = rotate;
        return *this;
    }

    bool TargetCtrl::isInAimRange(Vec2& outToPlayer) const
    {
        const auto& pos = m_body->getPos();
        // 基準点の計算
        auto pivot = pos + Vec2{ m_isMirrored ? 3 : -3, m_isFlipped ? -15 : 15 };
        pivot = pivot.rotateAt(pos, s3d::ToRadians(m_rotate));
        const Vec2 playerPos = ActorUtils::PlayerPos(*m_pActor);

        auto eyeVec = this->eyeVec();

        // 角度の計算
        outToPlayer = playerPos - pivot;

        auto axis = Axis2::FromRight(eyeVec);
        auto relativeToPlayer = axis.relative(outToPlayer);
        if (abyss::Math::IsZeroLoose(eyeVec.dot(Vec2{ 1, 0 }))) {
            if (-11 <= relativeToPlayer.y && relativeToPlayer.y <= 11) {
                relativeToPlayer.y = 0;
            }
        } else {
            if (-40 <= relativeToPlayer.y && relativeToPlayer.y <= 40) {
                relativeToPlayer.y = 0;
            }
        }
        outToPlayer = axis.global(relativeToPlayer);
        return outToPlayer.dot(eyeVec) > 0;
    }

    bool TargetCtrl::isInAimRangeWithDist() const
    {
        Vec2 toPlayer;
        bool isInRange = isInAimRange(toPlayer);
        constexpr double dist = 600;
        return isInRange && toPlayer.lengthSq() <= (dist * dist);
    }

    s3d::Vec2 TargetCtrl::eyeVec() const
    {
        return  Vec2{ m_isMirrored ? 1 : -1, 0 }.rotated(s3d::ToRadians(m_rotate));
    }

    s3d::Vec2 TargetCtrl::bazookaPos() const
    {
        const auto& pos = m_body->getPos();

        // 基準点の計算
        auto pivot = pos + Vec2{ m_isMirrored ? -3 : 3, m_isFlipped ? -15 : 15 };
        pivot = pivot.rotateAt(pos, s3d::ToRadians(m_rotate));
        auto pivot2 = pos + Vec2{ m_isMirrored ? 50 : -50, m_isFlipped ? -15 : 15 };
        pivot2 = pivot2.rotateAt(pos, s3d::ToRadians(m_rotate));

        return pivot2.rotateAt(pivot, s3d::ToRadians(m_bazookaRotate));
    }

    s3d::Vec2 TargetCtrl::bazookaVec() const
    {
        return  Vec2{ m_isMirrored ? 1 : -1, 0 }.rotated(s3d::ToRadians(m_rotate + m_bazookaRotate));
    }

    void TargetCtrl::onStart()
    {
        m_body = m_pActor->find<Body>();
    }

    void TargetCtrl::onLastUpdate()
    {
        if (!m_isFixBazooka) {
            auto dt = m_pActor->deltaTime();

            Vec2 toPlayer;
            if (m_isValidAim && this->isInAimRange(toPlayer)) {
                {
                    // 推測位置
                    Vec2 toPlayer2 = toPlayer + ActorUtils::PlayerVelocity(*m_pActor) * 1.5;
                    if (toPlayer.dot(toPlayer2) > 0) {
                        // 推測位置が交差していなければ差し替え
                        toPlayer = toPlayer2;
                    }
                }
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
            auto deltaRot = 50.0 * dt;
            if (m_bazookaRotateTarget > m_bazookaRotate + deltaRot) {
                m_bazookaRotate += deltaRot;
            } else if (m_bazookaRotateTarget < m_bazookaRotate - deltaRot) {
                m_bazookaRotate -= deltaRot;
            } else {
                m_bazookaRotate = m_bazookaRotateTarget;
            }
            m_bazookaRotate = InterpUtil::LerpDeg(
                m_bazookaRotate,
                m_bazookaRotateTarget,
                InterpUtil::DampRatio(0.005, dt)
            );
        }

        // Clamp
        if (m_isMirrored != m_isFlipped) {
            m_bazookaRotate = Clamp(m_bazookaRotate, -60.0, 0.0);
        } else {
            m_bazookaRotate = Clamp(m_bazookaRotate, 0.0, 60.0);
        }
    }
}
