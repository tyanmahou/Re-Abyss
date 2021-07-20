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
        m_hand->startForAttack(*m_body);
    }
    void AttackState::update()
    {
        auto dt = m_pActor->deltaTime();

        if (!m_hand->updateForAttack(
            m_isReturn,
            m_parent->getPos(),
            *m_body,
            dt
        )){
            this->changeState<PursuitState>();
        }
    }
}
