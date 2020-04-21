#include "CodeZeroHandAttakWaitState.hpp"
#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>
#include <abyss/params/Actors/CodeZero/CodeZeroParam.hpp>
#include <abyss/views/Actors/CodeZero/Hand/CodeZeroHandVM.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
namespace abyss
{
    CodeZeroHandAttackWaitState::CodeZeroHandAttackWaitState():
        m_timer(CodeZeroParam::Hand::AttackWaitTimeSec, true, WorldTime::TimeMicroSec)
    {}

    void CodeZeroHandAttackWaitState::start()
    {
        m_hand->startForAttackWait(*m_body);
    }

    void CodeZeroHandAttackWaitState::update(double dt)
    {
        if (m_timer.reachedZero()) {
            this->changeState(State::Attack);
            return;
        }
        m_body->update(dt);
    }

    void CodeZeroHandAttackWaitState::draw() const
    {
        m_actor->getBindedView()->drawAttackWait();
    }

}
