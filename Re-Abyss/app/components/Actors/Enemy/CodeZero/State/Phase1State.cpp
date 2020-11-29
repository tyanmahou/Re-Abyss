#include "Phase1State.hpp"
#include "Phase2State.hpp"
#include <abyss/params/Actors/Enemy/CodeZero/Param.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/Hand/HandActor.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Behavior.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    Phase1State::Phase1State()
    {
    }
    void Phase1State::start()
    {
        m_behavior->setBehavior(Behavior::Petern1);
    }
    void Phase1State::update([[maybe_unused]]double dt)
    {
        if (m_hp->value() <= Param::Base::Hp * 2 / 3) {
            if (m_parts->getLeftHand()->isPursuit() &&
                m_parts->getRightHand()->isPursuit()) {
                this->changeState<Phase2State>();
            }
            return;
        }
    }
}
