#include "ParentCtrl.hpp"
#include <abyss/controllers/Actors/Enemy/Slime/SlimeActor.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>

namespace abyss::Actor::Enemy::Slime::Sencer
{
    ParentCtrl::ParentCtrl(SlimeActor* parent):
        m_parent(parent)
    {}

    bool ParentCtrl::isWalk() const
    {
        return m_parent->isWalk();
    }

    const s3d::Vec2& ParentCtrl::getPos() const
    {
        return m_parent->getPos();
    }

    void ParentCtrl::reversed() const
    {
        m_parent->getBody().reversed();
    }

    Forward ParentCtrl::getForward() const
    {
        return m_parent->getBody().getForward();
    }

}

