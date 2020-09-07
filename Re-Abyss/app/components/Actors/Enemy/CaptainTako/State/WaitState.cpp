#include "WaitState.hpp"
#include "ChargeState.hpp"

#include <abyss/controllers/System/System.hpp>
#include <abyss/components/Actors/utils/ActorUtils.hpp>
#include <abyss/params/Actors/Enemy/CaptainTako/Param.hpp>

namespace abyss::Actor::Enemy::CaptainTako
{
    WaitState::WaitState()
    {}
    void WaitState::start()
    {
        m_waitTimer = ActorUtils::CreateTimer(*m_pActor, Param::Wait::TimeSec);
    }
    void WaitState::update([[maybe_unused]]double dt)
    {
        if (m_waitTimer.reachedZero() && m_pActor->getModule<Camera>()->inScreen(m_body->getPos())) {
            this->changeState<ChargeState>();
        }
    }

    void WaitState::draw() const
    {
        (*m_view)->drawWait();
    }
}
