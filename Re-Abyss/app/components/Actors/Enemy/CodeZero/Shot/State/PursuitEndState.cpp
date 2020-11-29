#include "PursuitEndState.hpp"
#include <abyss/components/Actors/utils/ActorUtils.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/ShotParam.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    PursuitEndState::PursuitEndState()
    {}

    void PursuitEndState::start()
    {
        m_timer = ActorUtils::CreateTimer(*m_pActor, ShotParam::Pursuit::EndToDeadTimeSec);
    }
    void PursuitEndState::update()
    {
        if (m_timer.reachedZero()) {
            m_pActor->destroy();
        }
    }
}
