#include "PursuitEndState.hpp"
#include <abyss/controllers/World/WorldTime.hpp>
namespace abyss::CodeZero::Shot
{
    PursuitEndState::PursuitEndState():
        m_timer(3.5s, true, WorldTime::TimeMicroSec)
    {}

    void PursuitEndState::update([[maybe_unused]]double dt)
    {
        if (m_timer.reachedZero()) {
            m_actor->destroy();
        }
        m_body->update(dt);
    }
}
