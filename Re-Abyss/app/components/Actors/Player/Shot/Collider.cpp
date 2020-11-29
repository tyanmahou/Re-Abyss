#include "Collider.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Player/Shot/PlayerShot.hpp>

namespace abyss::Actor::Player::Shot
{
    void Collider::onStart()
    {
        m_body = m_pActor->find<Body>();
        m_shot = m_pActor->find<PlayerShot>();
    }

    s3d::Circle Collider::getColliderCircle() const
    {
        return s3d::Circle(m_body->getPos(), m_shot->toRadius());
    }

    CShape Collider::getCollider()const
    {
        return this->getColliderCircle();
    }
}

