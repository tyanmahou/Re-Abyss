#include "Phase3State.hpp"
#include <abyss/params/Actors/Enemy/CodeZero/Param.hpp>
#include <abyss/controllers/Actors/Enemy/CodeZero/Hand/HandActor.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Behavior.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    Phase3State::Phase3State()
    {

    }
    void Phase3State::start()
    {
        m_behavior->setBehavior(Behavior::Petern3);
    }
    void Phase3State::update([[maybe_unused]]double dt)
    {
        if (m_hp->isDead()) {
            return;
        }
    }
}
