#include "WaitState.hpp"
#include <abyss/views/Actors/Schield/SchieldVM.hpp>
#include <abyss/params/Actors/Schield/Param.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/models/Collision/CollisionUtil.hpp>

namespace abyss::Schield
{
    WaitState::WaitState() :
        m_timer(Param::Wait::TimeSec, true, WorldTime::TimeMicroSec)
    {}
    void WaitState::update(double dt)
    {
        BaseState::update(dt);

        if (m_timer.reachedZero() && m_actor->getModule<Camera>()->inScreen(m_body->getPos())) {
            this->changeState(State::AttackPlus);
        }
    }

    void WaitState::draw() const
    {
        m_actor->getBindedView()->drawWait();
    }

    void WaitState::onCollisionStay(ICollider * col)
    {
        BaseState::onCollisionStay(col);
        // damage only wait state
        if (ColisionUtil::Intersects(col->getCollider(), m_actor->getFaceCollider())) {
            // face only
            m_actor->EnemyActor::onCollisionStay(col);
        }
    }

}
