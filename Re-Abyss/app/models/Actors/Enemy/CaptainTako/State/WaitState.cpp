#include "WaitState.hpp"
#include <abyss/views/Actors/Enemy/CaptainTako/CpatainTakoVM.hpp>
#include <abyss/controllers/System/System.hpp>
#include <abyss/models/Actors/utils/ActorUtils.hpp>
#include <abyss/params/Actors/Enemy/CaptainTako/Param.hpp>

namespace abyss::CaptainTako
{
    WaitState::WaitState()
    {}
    void WaitState::start()
    {
        m_waitTimer = ActorUtils::CreateTimer(*m_pActor, Param::Wait::TimeSec);
    }
    void WaitState::update(double dt)
    {
        if (m_waitTimer.reachedZero() && m_pActor->getModule<Camera>()->inScreen(m_body->getPos())) {
            this->changeState(CaptainTakoActor::State::Charge);
        }
        BaseState::update(dt);
    }

    void WaitState::draw() const
    {
        m_pActor->getBindedView()->drawWait();
    }
}
