#include "PursuitState.hpp"
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/models/Actors/utils/ActorUtils.hpp>
#include <abyss/params/Actors/CodeZero/ShotParam.hpp>
namespace abyss::CodeZero::Shot
{
    PursuitState::PursuitState():
        m_timer(ShotParam::Pursuit::TimeSec, true, WorldTime::TimeMicroSec)
    {
    }
    void PursuitState::update(double dt)
    {
        if (m_timer.reachedZero()) {
            this->changeState(State::PursuitEnd);
            return;
        }
        auto diff = ActorUtils::PlayerDiffVec(*m_actor, *m_body);
        m_body->setVelocity(diff.normalized() * ShotParam::Pursuit::Speed);

        m_body->update(dt);
    }
}
