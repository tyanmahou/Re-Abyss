#include "AttackState.hpp"
#include "PursuitState.hpp"
#include <abyss/params/Actor/Enemy/CodeZero/Param.hpp>

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
        if (!m_handMove->updateForAttack()){
            this->changeState<PursuitState>();
        }
    }
}
