#include "PursuitState.hpp"
#include "PursuitEndState.hpp"

#include <abyss/components/Actors/utils/ActorUtils.hpp>
#include <abyss/params/Actors/Enemy/CodeZero/ShotParam.hpp>
namespace abyss::Actor::Enemy::CodeZero::Shot
{
    PursuitState::PursuitState()
    {
    }
    Task<> PursuitState::start()
    {
        m_timer = ActorUtils::CreateTimer(*m_pActor, ShotParam::Pursuit::TimeSec);
        co_return;
    }
    void PursuitState::update()
    {
        if (m_timer.reachedZero()) {
            this->changeState<PursuitEndState>();
            return;
        }
        auto diff = ActorUtils::PlayerDiffVec(*m_pActor, *m_body);
        m_body->setVelocity(diff.normalized() * ShotParam::Pursuit::Speed);
    }
}
