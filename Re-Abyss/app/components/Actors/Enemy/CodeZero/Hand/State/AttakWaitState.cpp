#include "AttakWaitState.hpp"
#include "AttackState.hpp"
#include <abyss/params/Actors/Enemy/CodeZero/HandParam.hpp>
#include <abyss/views/Actors/Enemy/CodeZero/Hand/HandVM.hpp>
#include <abyss/components/Actors/utils/ActorUtils.hpp>
namespace abyss::Actor::Enemy::CodeZero::Hand
{
    AttackWaitState::AttackWaitState()
    {}

    Task<> AttackWaitState::start()
    {
        m_timer = ActorUtils::CreateTimer(*m_parent->getParent(), HandParam::Attack::WaitTimeSec);
        m_hand->startForAttackWait(*m_body);
        co_return;
    }

    void AttackWaitState::update()
    {
        auto dt = m_pActor->deltaTime();
        if (m_timer.reachedZero()) {
            this->changeState<AttackState>();
            return;
        }
    }

    void AttackWaitState::draw() const
    {
        (*m_view)->drawAttackWait();
    }

}
