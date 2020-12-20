#include "Phase3State.hpp"
#include <abyss/params/Actors/Enemy/CodeZero/Param.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Behavior.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    Phase3State::Phase3State()
    {

    }
    Task<> Phase3State::start()
    {
        m_behavior->setBehavior(Behavior::Petern3);
        co_return;
    }
    void Phase3State::update()
    {
        if (m_hp->isDead()) {
            return;
        }
    }
}
