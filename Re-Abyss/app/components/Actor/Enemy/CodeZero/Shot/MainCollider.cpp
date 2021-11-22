#include "MainCollider.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/ScaleCtrl.hpp>

#include <abyss/params/Actor/Enemy/CodeZero/ShotParam.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    void MainCollider::onStart()
    {
        m_body = m_pActor->find<Body>();
        m_scale = m_pActor->find<ScaleCtrl>();
    }
    CShape MainCollider::getCollider() const
    {
        return s3d::Circle(m_body->getPos(), ShotParam::Base::ColRadius * m_scale->get());
    }
    MainCollider::MainCollider(ActorObj* pActor) :
        m_pActor(pActor)
    {}
}
