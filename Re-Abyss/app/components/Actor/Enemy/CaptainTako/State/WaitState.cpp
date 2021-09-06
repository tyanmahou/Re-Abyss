#include "WaitState.hpp"
#include "ChargeState.hpp"
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/params/Actor/Enemy/CaptainTako/Param.hpp>

namespace abyss::Actor::Enemy::CaptainTako
{
    WaitState::WaitState()
    {}
    void WaitState::start()
    {
        m_waitTimer = ActorUtils::CreateTimer(*m_pActor, Param::Wait::TimeSec);
        m_motion->set(Motion::Wait);
    }
    void WaitState::update()
    {
        if (m_waitTimer.reachedZero() && m_pActor->getModule<Camera>()->inScreen(m_body->getPos())) {
            this->changeState<ChargeState>();
        }
    }
}
