#include <abyss/components/Actor/Enemy/BabyDux/EyeCtrl.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Enemy/BabyDux/ForwardCtrl.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/params/Actor/Enemy/BabyDux/Param.hpp>
#include <abyss/utils/Math/InterpUtil.hpp>
#include <abyss/utils/Math/Math.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::BabyDux
{
    EyeCtrl::EyeCtrl(ActorObj* pActor) :
        m_pActor(pActor)
    {}
    void EyeCtrl::setup(Executer executer)
    {
        executer.on<ILastUpdate>().addAfter<ForwardCtrl>();
    }
    void EyeCtrl::onStart()
    {
        m_body = m_pActor->find<Body>();
    }
    void EyeCtrl::onLastUpdate()
    {
        const auto& pos = m_body->getPos();
        const auto& playerPos = ActorUtils::PlayerPos(*m_pActor);

        auto erpRate = InterpUtil::DampRatio(Param::Eye::ErpRate, m_pActor->deltaTime());

        auto moveEye = [&](Vec2& eyePos, const Vec2& offset, const Vec2& limitBegin, const Vec2& limitEnd) {

            Vec2 targetPos{ 0, 0 };
            const auto toPlayerPos = playerPos - (pos + (offset * -m_body->getForward().toVec2()) + Vec2{ 0, 10 });
            auto toPlayerUnit = s3d::Vec2::Zero();
            if (!toPlayerPos.isZero()) {
                toPlayerUnit = toPlayerPos.normalized();
            }
            const double dist = s3d::Min(toPlayerPos.length() * Param::Eye::DistRate,Param::Eye::Dist);

            targetPos = toPlayerUnit * dist;

            const auto linearFunc = Math::LinearFunc(limitBegin, limitEnd);

            if (auto limitY = linearFunc(targetPos.x);  targetPos.y < limitY) {
                targetPos.y = limitY;
            }
            eyePos = s3d::Math::Lerp(eyePos, targetPos, erpRate);
        };

        // 眼を動かす
#define MOVE_EYE(Kind) moveEye(m_eyePos##Kind, Param::Base::Eye##Kind, Param::Eye::LimitBegin##Kind, Param::Eye::LimitEnd##Kind)

        MOVE_EYE(L);
        MOVE_EYE(R);

#undef MOVE_EYE
    }
}
