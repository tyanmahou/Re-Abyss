#include "SchieldWaitState.hpp"
#include <abyss/views/Actors/Schield/SchieldVM.hpp>
#include <abyss/params/Actors/Schield/SchieldParam.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/models/Collision/CollisionUtil.hpp>

namespace abyss
{
    SchieldWaitState::SchieldWaitState() :
        m_timer(SchieldParam::Wait::TimeSec, true, WorldTime::TimeMicroSec)
    {}
    void SchieldWaitState::update(double dt)
    {
        SchieldBaseState::update(dt);

        if (m_timer.reachedZero() && ActionSystem::Camera()->inScreen(m_body->getPos())) {
            this->changeState(SchieldActor::State::AttackPlus);
        }
    }

    void SchieldWaitState::draw() const
    {
        m_actor->getBindedView()->drawWait();
    }

    void SchieldWaitState::onCollisionStay(ICollider * col)
    {
        SchieldBaseState::onCollisionStay(col);
        // damage only wait state
        if (ColisionUtil::Intersects(col->getCollider(), m_actor->getFaceCollider())) {
            // face only
            m_actor->EnemyActor::onCollisionStay(col);
        }
    }

}
