#include "AttakWaitState.hpp"
#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>
#include <abyss/params/Actors/CodeZero/HandParam.hpp>
#include <abyss/views/Actors/CodeZero/Hand/HandVM.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
namespace abyss::CodeZero::Hand
{
    AttackWaitState::AttackWaitState():
        m_timer(HandParam::Attack::WaitTimeSec, true, WorldTime::TimeMicroSec)
    {}

    void AttackWaitState::start()
    {
        m_hand->startForAttackWait(*m_body);
    }

    void AttackWaitState::update(double dt)
    {
        if (m_timer.reachedZero()) {
            this->changeState(State::Attack);
            return;
        }
        m_body->update(dt);
    }

    void AttackWaitState::draw() const
    {
        m_actor->getBindedView()->drawAttackWait();
    }

}
