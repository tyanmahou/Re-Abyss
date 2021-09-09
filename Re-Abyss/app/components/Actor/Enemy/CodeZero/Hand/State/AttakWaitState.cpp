#include "AttakWaitState.hpp"
#include "AttackState.hpp"
#include <abyss/params/Actor/Enemy/CodeZero/HandParam.hpp>
#include <abyss/views/Actor/Enemy/CodeZero/Hand/HandVM.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
namespace abyss::Actor::Enemy::CodeZero::Hand
{
    AttackWaitState::AttackWaitState()
    {}

    void AttackWaitState::start()
    {
        m_motion->set(Motion::AttackWait);
    }

    void AttackWaitState::end()
    {
        m_motion->set(Motion::Wait);
    }

    Task<> AttackWaitState::task()
    {
        m_handMove->startForAttackWait();

        // 一定時間追従
        co_yield BehaviorUtils::WaitForSeconds(m_parent->getParent(), HandParam::Attack::WaitTimeSec);

        // 攻撃
        this->changeState<AttackState>();
        co_return;
    }

    void AttackWaitState::update()
    {
    }
}
