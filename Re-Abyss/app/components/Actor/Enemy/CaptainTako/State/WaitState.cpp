#include "WaitState.hpp"
#include "ChargeState.hpp"
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/params/Actor/Enemy/CaptainTako/Param.hpp>

namespace abyss::Actor::Enemy::CaptainTako
{
    WaitState::WaitState():
        m_waitTimer(Param::Wait::TimeSec)
    {}
    void WaitState::start()
    {
        m_motion->set(Motion::Wait);
    }
    void WaitState::update()
    {
        m_waitTimer.update(m_pActor->deltaTime());
        if (m_waitTimer.isEnd() && m_pActor->getModule<Camera>()->inScreen(m_body->getPos())) {
            this->changeState<ChargeState>();
        }
    }
}
