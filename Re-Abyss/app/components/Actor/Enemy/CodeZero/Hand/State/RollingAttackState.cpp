#include "RollingAttackState.hpp"
#include "AttackWaitState.hpp"
namespace abyss::Actor::Enemy::CodeZero::Hand
{
    RollingAttackState::RollingAttackState()
    {}
    void RollingAttackState::start()
    {
        m_handMove->startForRollingAttack();
    }
    void RollingAttackState::update()
    {
        if (m_handMove->isMoveEnd()) {
            this->changeState<AttackWaitState>();
        }
    }
}
