#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/RollingAttackState.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/AttackWaitState.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    RollingAttackState::RollingAttackState(bool isReverse):
        m_isReverse(isReverse)
    {}
    void RollingAttackState::start()
    {
        m_handMove->startForRollingAttack(m_isReverse);
    }
    void RollingAttackState::update()
    {
        if (m_handMove->isMoveEnd()) {
            this->changeState<AttackWaitState>();
        }
    }
}
