#include "Phase1State.hpp"
#include "Phase2State.hpp"
#include <abyss/params/Actor/Enemy/CodeZero/Param.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/HandProxy.h>
#include <abyss/components/Actor/Enemy/CodeZero/Behavior.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    Phase1State::Phase1State()
    {
    }
    Task<> Phase1State::start()
    {
        m_behavior->setBehavior(Behavior::Petern1);
        co_return;
    }
    void Phase1State::update()
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
