#include "PursuitEndState.hpp"
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/params/Actors/CodeZero/ShotParam.hpp>

namespace abyss::CodeZero::Shot
{
    PursuitEndState::PursuitEndState():
        m_timer(ShotParam::Pursuit::EndToDeadTimeSec, true, WorldTime::TimeMicroSec)
    {}

    void PursuitEndState::update([[maybe_unused]]double dt)
    {
        if (m_timer.reachedZero()) {
            m_actor->destroy();
        }
        m_body->update(dt);
    }
}
