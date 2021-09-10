#include "AttackState.hpp"
#include "PursuitState.hpp"

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    AttackState::AttackState()
    {
    
    }
    void AttackState::start()
    {
        m_handMove->startForAttack();
    }
    void AttackState::update()
    {
        if (m_handMove->isMoveEnd()){
            this->changeState<PursuitState>();
        }
    }
}
