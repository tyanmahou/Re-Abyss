#include "CodeZeroHandAttackState.hpp"
#include <abyss/params/Actors/CodeZero/CodeZeroParam.hpp>
#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>

namespace abyss
{
    CodeZeroHandAttackState::CodeZeroHandAttackState()
    {}
    void CodeZeroHandAttackState::start()
    {
        m_hand->startForAttack(*m_body);
    }
    void CodeZeroHandAttackState::update(double dt)
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
