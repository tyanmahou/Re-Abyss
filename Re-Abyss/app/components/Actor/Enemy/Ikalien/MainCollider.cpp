#include <abyss/components/Actor/Enemy/Ikalien/MainCollider.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>

#include <abyss/params/Actor/Enemy/Ikalien/Param.hpp>

namespace abyss::Actor::Enemy::Ikalien
{
    void MainCollider::onStart()
    {
        m_body = m_pActor->find<Body>();
    }
    CShape MainCollider::getCollider() const
    {
        return s3d::Circle(m_body->getCenterPos(), Param::Base::ColRadius);
    }
    MainCollider::MainCollider(ActorObj* pActor) :
        m_pActor(pActor)
    {}
}
