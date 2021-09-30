#include "PursuitState.hpp"
#include "PursuitEndState.hpp"

#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/params/Actor/Enemy/CodeZero/ShotParam.hpp>
namespace abyss::Actor::Enemy::CodeZero::Shot
{
    PursuitState::PursuitState():
        m_timer(ShotParam::Pursuit::TimeSec)
    {
    }
    void PursuitState::start()
    {
    }
    void PursuitState::update()
    {
        m_timer.update(m_pActor->deltaTime());
        if (m_timer.isEnd()) {
            this->changeState<PursuitEndState>();
            return;
        }
        auto diff = ActorUtils::PlayerDiffVec(*m_pActor, *m_body);
        m_body->setVelocity(diff.normalized() * ShotParam::Pursuit::Speed);
    }
}
