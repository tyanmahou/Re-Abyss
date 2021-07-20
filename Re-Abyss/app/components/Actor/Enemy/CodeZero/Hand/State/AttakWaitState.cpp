#include "AttakWaitState.hpp"
#include "AttackState.hpp"
#include <abyss/params/Actor/Enemy/CodeZero/HandParam.hpp>
#include <abyss/views/Actor/Enemy/CodeZero/Hand/HandVM.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
namespace abyss::Actor::Enemy::CodeZero::Hand
{
    AttackWaitState::AttackWaitState()
    {}

    Task<> AttackWaitState::task()
    {
        m_hand->startForAttackWait(*m_body);

        // 一定時間追従
        co_yield BehaviorUtils::WaitForSeconds(m_parent->getParent(), HandParam::Attack::WaitTimeSec);

        // 攻撃
        this->changeState<AttackState>();
        co_return;
    }

    void AttackWaitState::update()
    {
    }

    void AttackWaitState::draw() const
    {
        (*m_view)->drawAttackWait();
    }

}
