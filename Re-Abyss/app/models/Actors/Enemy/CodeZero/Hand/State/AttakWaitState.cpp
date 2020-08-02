#include "AttakWaitState.hpp"
#include "AttackState.hpp"
#include <abyss/controllers/Actors/Enemy/CodeZero/CodeZeroActor.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/HandParam.hpp>
#include <abyss/views/Actors/Enemy/CodeZero/Hand/HandVM.hpp>
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
            this->changeState<AttackState>();
            return;
        }
        m_body->update(dt);
    }

    void AttackWaitState::draw() const
    {
        (*m_view)->drawAttackWait();
    }

}
