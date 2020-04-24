#include "AttackState.hpp"
#include <abyss/params/Actors/CodeZero/Param.hpp>
#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>

namespace abyss::CodeZero::Hand
{
    AttackState::AttackState()
    {}
    void AttackState::start()
    {
        m_hand->startForAttack(*m_body);
    }
    void AttackState::update(double dt)
    {
        m_hand->updateForAttack(
            m_isReturn,
            m_parent->getPos(),
            *m_body,
            dt,
            [this]() {this->changeState(State::Pursuit);}
        );
    }
}
