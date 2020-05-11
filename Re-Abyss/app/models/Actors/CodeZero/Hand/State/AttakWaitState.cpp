#include "AttakWaitState.hpp"
#include <abyss/controllers/Actors/Enemy/CodeZero/CodeZeroActor.hpp>
#include <abyss/params/Actors/CodeZero/HandParam.hpp>
#include <abyss/views/Actors/CodeZero/Hand/HandVM.hpp>
#include <abyss/models/Actors/utils/ActorUtils.hpp>
namespace abyss::CodeZero::Hand
{
    AttackWaitState::AttackWaitState()
    {}

    void AttackWaitState::start()
    {
        m_timer = ActorUtils::CreateTimer(*m_parent, HandParam::Attack::WaitTimeSec);
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
        m_pActor->getBindedView()->drawAttackWait();
    }

}
