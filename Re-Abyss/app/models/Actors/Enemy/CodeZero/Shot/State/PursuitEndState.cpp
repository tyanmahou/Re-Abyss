#include "PursuitEndState.hpp"
#include <abyss/models/Actors/utils/ActorUtils.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/ShotParam.hpp>

namespace abyss::CodeZero::Shot
{
    PursuitEndState::PursuitEndState()
    {}

    void PursuitEndState::start()
    {
        m_timer = ActorUtils::CreateTimer(*m_pActor, ShotParam::Pursuit::EndToDeadTimeSec);
    }
    void PursuitEndState::update([[maybe_unused]]double dt)
    {
        if (m_timer.reachedZero()) {
            m_pActor->destroy();
        }
        m_body->update(dt);
    }
}
