#include "PursuitState.hpp"
#include <abyss/models/Actors/utils/ActorUtils.hpp>
#include <abyss/params/Actors/CodeZero/ShotParam.hpp>
namespace abyss::CodeZero::Shot
{
    PursuitState::PursuitState()
    {
    }
    void PursuitState::start()
    {
        m_timer = ActorUtils::CreateTimer(*m_pActor, ShotParam::Pursuit::TimeSec);
    }
    void PursuitState::update(double dt)
    {
        if (m_timer.reachedZero()) {
            this->changeState(State::PursuitEnd);
            return;
        }
        auto diff = ActorUtils::PlayerDiffVec(*m_pActor, *m_body);
        m_body->setVelocity(diff.normalized() * ShotParam::Pursuit::Speed);

        m_body->update(dt);
    }
}
