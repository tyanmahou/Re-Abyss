#include "WaitState.hpp"
#include "PursuitState.hpp"

#include <abyss/params/Actor/Enemy/LaunShark/ShotParam.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>

namespace abyss::Actor::Enemy::LaunShark::Shot
{
    WaitState::WaitState()
    {}
    Task<> WaitState::start()
    {
        m_body->noneResistanced();
        m_timer = ActorUtils::CreateTimer(*m_pActor, ShotParam::Wait::Time);
        co_return;
    }
    void WaitState::update()
    {
        m_body->setVelocity(m_rotate->getDir9() * ShotParam::Wait::Speed);
        if (m_timer.reachedZero()) {
            this->changeState<PursuitState>();
        }
    }

    void WaitState::draw() const
    {
        (*m_view)->drawWait();
    }
}
