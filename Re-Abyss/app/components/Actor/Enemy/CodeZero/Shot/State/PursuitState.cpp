#include <abyss/components/Actor/Enemy/CodeZero/Shot/State/PursuitState.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Shot/State/PursuitEndState.hpp>

#include <abyss/components/Actor/Enemy/CodeZero/Shot/ShotProxy.hpp>
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
        m_pActor->find<ShotProxy>()->startPursuit();
    }
    void PursuitState::update()
    {
        m_timer.update(m_pActor->deltaTime());
        if (m_timer.isEnd()) {
            this->changeState<PursuitEndState>();
            return;
        }
        auto diff = ActorUtils::ToPlayer(*m_pActor, *m_body);
        m_body->setVelocity(diff.normalized() * ShotParam::Pursuit::Speed);
    }
}
