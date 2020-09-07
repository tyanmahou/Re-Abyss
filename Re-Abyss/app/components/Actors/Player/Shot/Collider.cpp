#include "Collider.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/components/Actors/Player/Shot/PlayerShotModel.hpp>

namespace abyss::Actor::Player::Shot
{
    void Collider::setup()
    {
        m_body = m_pActor->find<BodyModel>();
        m_shot = m_pActor->find<PlayerShotModel>();
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

