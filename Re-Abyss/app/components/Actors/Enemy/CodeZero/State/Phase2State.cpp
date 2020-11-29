#include "Phase2State.hpp"
#include "Phase3State.hpp"
#include <abyss/params/Actors/Enemy/CodeZero/Param.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/Hand/HandActor.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Behavior.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    Phase2State::Phase2State()
    {

    }
    void Phase2State::start()
    {
        m_behavior->setBehavior(Behavior::Petern2);
    }
    void Phase2State::update()
    {
        if (m_hp->value() <= Param::Base::Hp * 1 / 3) {
            if (m_parts->getLeftHand()->isPursuit() &&
                m_parts->getRightHand()->isPursuit()) {
                this->changeState<Phase3State>();
            }
            return;
        }
    }
}
