#include "EyeCtrl.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/HP.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/params/Actor/Enemy/KingDux/Param.hpp>
#include <abyss/utils/Interp/InterpUtil.hpp>
#include <abyss/utils/Math/Math.hpp>
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
        m_damage = m_pActor->find<DamageCtrl>();
    }
    void EyeCtrl::onLastUpdate()
    {
        const auto& pos = m_body->getPos();
        const auto& playerPos = ActorUtils::PlayerPos(*m_pActor);

        auto erpRate = InterpUtil::DampRatio(Param::Eye::ErpRate, m_pActor->deltaTime());

        auto moveEye = [&](Vec2& eyePos, const Vec2& offset, const Vec2& limitBegin, const Vec2& limitEnd) {

            Vec2 targetPos{0, 0};
            if (m_toCenterEye || m_hp->isDead() || m_damage->isInInvincibleTime()) {
                targetPos = Vec2{ 0, 20 };
                erpRate = InterpUtil::DampRatio(Param::Eye::DamageErpRate, m_pActor->deltaTime());
            } else {
                const auto toPlayerPos = playerPos - (pos + offset + Vec2{ 0, 10 });
                auto toPlayerUnit = s3d::Vec2::Zero();
                if (!toPlayerPos.isZero()) {
                    toPlayerUnit = toPlayerPos.normalized();
                }
                const double dist = s3d::Min(toPlayerPos.length() * Param::Eye::DistRate, 65.0);

                targetPos = toPlayerUnit * dist;

                const auto linearFunc = Math::LinearFunc(limitBegin, limitEnd);

                if (auto limitY = linearFunc(targetPos.x);  targetPos.y < limitY) {
                    targetPos.y = limitY;
                }
            }
            eyePos = s3d::Math::Lerp(eyePos, targetPos, erpRate);
        };

        // 眼を動かす
#define MOVE_EYE(Kind) moveEye(m_eyePos##Kind, Param::Base::Eye##Kind, Param::Eye::LimitBegin##Kind, Param::Eye::LimitEnd##Kind)

        MOVE_EYE(L);
        MOVE_EYE(R);

#undef MOVE_EYE
    }
    void EyeCtrl::onStateStart()
    {
        m_toCenterEye = false;
    }
    void EyeCtrl::requestToCenterEye()
    {
        m_toCenterEye = true;
    }
}
