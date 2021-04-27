#include "Collider.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Player/Shot/PlayerShot.hpp>
#include <abyss/params/Actor/Player/ShotParam.hpp>

namespace abyss::Actor::Player::Shot
{
    Collider::Collider(ActorObj* pActor):
        m_pActor(pActor)
    {}
    void Collider::onStart()
    {
        m_body = m_pActor->find<Body>();
        m_shot = m_pActor->find<PlayerShot>();
    }

    s3d::Circle Collider::getColliderCircle() const
    {
        return s3d::Circle(m_body->getPos(), m_shot->toRadius() * ShotParam::Base::ColliderRate);
    }

    CShape Collider::getCollider()const
    {
        return this->getColliderCircle();
    }
}

