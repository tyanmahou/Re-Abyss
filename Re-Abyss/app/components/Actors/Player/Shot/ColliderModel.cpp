#include "ColliderModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/components/Actors/Player/Shot/PlayerShotModel.hpp>

namespace abyss::Actor::Player::Shot
{
    void ColliderModel::setup()
    {
        m_body = m_pActor->find<BodyModel>();
        m_shot = m_pActor->find<PlayerShotModel>();
    }

    s3d::Circle ColliderModel::getColliderCircle() const
    {
        return s3d::Circle(m_body->getPos(), m_shot->toRadius());
    }

    CShape ColliderModel::getCollider()const
    {
        return this->getColliderCircle();
    }
}

