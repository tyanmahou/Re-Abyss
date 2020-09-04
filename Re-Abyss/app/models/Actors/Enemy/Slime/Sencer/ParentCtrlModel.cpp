#include "ParentCtrlModel.hpp"
#include <abyss/controllers/Actors/Enemy/Slime/SlimeActor.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>

namespace abyss::Actor::Enemy::Slime::Sencer
{
    ParentCtrlModel::ParentCtrlModel(SlimeActor* parent):
        m_parent(parent)
    {}

    bool ParentCtrlModel::isWalk() const
    {
        return m_parent->isWalk();
    }

    const s3d::Vec2& ParentCtrlModel::getPos() const
    {
        return m_parent->getPos();
    }

    void ParentCtrlModel::reversed() const
    {
        m_parent->getBody().reversed();
    }

    Forward ParentCtrlModel::getForward() const
    {
        return m_parent->getBody().getForward();
    }

}

