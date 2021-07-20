#include "Phase3State.hpp"
#include <abyss/params/Actor/Enemy/CodeZero/Param.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Behavior.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    Phase3State::Phase3State()
    {

    }
    void Phase3State::start()
    {
        m_behavior->setBehavior(Behavior::Petern3);
    }
    void Phase3State::update()
    {
        if (m_hp->isDead()) {
            return;
        }
    }
}
