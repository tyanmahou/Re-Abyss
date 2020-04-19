#include "CodeZeroHandAttakWaitState.hpp"
#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>
#include <abyss/params/Actors/CodeZero/CodeZeroParam.hpp>
#include <abyss/views/Actors/CodeZero/Hand/CodeZeroHandVM.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
namespace abyss
{
    void CodeZeroHandAttackWaitState::updateRight(double dt)
    {
        m_body->update(dt);
    }

    void CodeZeroHandAttackWaitState::updateLeft(double dt)
    {
        return this->updateRight(dt);
    }

    CodeZeroHandAttackWaitState::CodeZeroHandAttackWaitState():
        m_timer(CodeZeroParam::Hand::AttackWaitTimeSec, true, WorldTime::TimeMicroSec)
    {}

    void CodeZeroHandAttackWaitState::start()
    {
        if (m_actor->isLeftHand()) {
            m_body->setVelocityY(0);
            m_body->setVelocityX(10);
        } else {
            m_body->setVelocityY(-10);
            m_body->setVelocityX(0);
        }
    }

    void CodeZeroHandAttackWaitState::update(double dt)
    {
        if (m_timer.reachedZero()) {
            this->changeState(State::Attack);
            return;
        }
        CodeZeroHandBaseState::update(dt);
    }

    void CodeZeroHandAttackWaitState::draw() const
    {
        m_actor->getBindedView()->drawAttackWait();
    }

}
