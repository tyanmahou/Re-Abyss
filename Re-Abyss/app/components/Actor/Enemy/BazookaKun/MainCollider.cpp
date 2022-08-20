#include <abyss/components/Actor/Enemy/BazookaKun/MainCollider.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/params/Actor/Enemy/BazookaKun/Param.hpp>

namespace abyss::Actor::Enemy::BazookaKun
{
    MainCollider::MainCollider(ActorObj* pActor):
        m_pActor(pActor)
    {}
    void MainCollider::onStart()
    {
        m_body = m_pActor->find<Body>();
        m_target = m_pActor->find<TargetCtrl>();
    }

    CShape MainCollider::getCollider() const
    {
        const auto& pos = m_body->getPos();
        // 基準点の計算
        return RectF{ pos - Vec2{40, m_target->isFlipped() ? 30 : 10}, Param::Base::BodySize }
        .rotatedAt(pos, s3d::ToRadians(m_target->rotate()));
    }
}
