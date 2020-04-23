#include "PursuitState.hpp"
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/Actors/utils/ActorUtils.hpp>

namespace abyss::CodeZero::Shot
{
    PursuitState::PursuitState():
        m_timer(5s, true, WorldTime::TimeMicroSec)
    {
    }
    void PursuitState::update(double dt)
    {
        if (m_timer.reachedZero()) {
            this->changeState(State::PursuitEnd);
            return;
        }
        auto diff = ActorUtils::PlayerDiffVec(*m_actor, *m_body);
        m_body->setVelocity(diff.normalized() * 90);

        m_body->update(dt);
    }
}
