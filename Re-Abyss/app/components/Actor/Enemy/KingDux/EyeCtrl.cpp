#include "EyeCtrl.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/HP.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/params/Actor/Enemy/KingDux/Param.hpp>
#include <abyss/utils/Interp/InterpUtil.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    EyeCtrl::EyeCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}
    void EyeCtrl::onStart()
    {
        m_body = m_pActor->find<Body>();
        m_hp = m_pActor->find<HP>();
    }
    void EyeCtrl::onLastUpdate()
    {
        const auto& pos = m_body->getPos();
        const auto& playerPos = ActorUtils::PlayerPos(*m_pActor);

        auto erpRate = InterpUtil::DampRatio(Param::Eye::ErpRate, m_pActor->deltaTime());

        auto moveEye = [&](Vec2& eyePos, const Vec2& offset) {

            Vec2 targetPos{0, 0};
            if (m_hp->isDead() || m_hp->isInInvincibleTime()) {
                targetPos = Vec2{ 0, 20 };
                erpRate = 0.5;
            } else {
                const auto toPlayerPos = playerPos - (pos + offset + Vec2{ 0, 10 });
                auto toPlayerUnit = s3d::Vec2::Zero();
                if (!toPlayerPos.isZero()) {
                    toPlayerUnit = toPlayerPos.normalized();
                }
                const double dist = s3d::Min(toPlayerPos.length() * Param::Eye::DistRate, 65.0);

                targetPos = toPlayerUnit * dist;
            }
            eyePos = s3d::Math::Lerp(eyePos, targetPos, erpRate);
        };

        // 眼を動かす
        moveEye(m_eyePosL, Param::Base::EyeL);
        moveEye(m_eyePosR, Param::Base::EyeR);
    }
}
