#include "WaitState.hpp"
#include "ChargeState.hpp"

#include <abyss/controllers/System/System.hpp>
#include <abyss/components/Actors/utils/ActorUtils.hpp>
#include <abyss/params/Actors/Enemy/CaptainTako/Param.hpp>

namespace abyss::Actor::Enemy::CaptainTako
{
    WaitState::WaitState()
    {}
    Task<> WaitState::start()
    {
        m_waitTimer = ActorUtils::CreateTimer(*m_pActor, Param::Wait::TimeSec);
        co_return;
    }
    void WaitState::update()
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
