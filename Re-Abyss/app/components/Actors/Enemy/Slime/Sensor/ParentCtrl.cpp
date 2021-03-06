#include "ParentCtrl.hpp"
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Enemy/Slime/State/WalkState.hpp>

namespace abyss::Actor::Enemy::Slime::Sensor
{
    ParentCtrl::ParentCtrl(IActor* parent):
        m_parent(parent)
    {}

    void ParentCtrl::onStart()
    {
        m_state = m_parent->find<StateCtrl>();
        m_body = m_parent->find<Body>();
    }
    bool ParentCtrl::isWalk() const
    {
        return m_state->isState<WalkState>();
    }

    const s3d::Vec2& ParentCtrl::getPos() const
    {
        return m_body->getPos();
    }

    void ParentCtrl::reversed() const
    {
        m_body->reversed();
    }

    Forward ParentCtrl::getForward() const
    {
        return m_body->getForward();
    }

}

