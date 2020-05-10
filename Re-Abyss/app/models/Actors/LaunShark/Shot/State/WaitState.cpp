#include "WaitState.hpp"
#include <abyss/controllers/World/WorldTime.hpp>

#include <abyss/params/Actors/LaunShark/ShotParam.hpp>
#include <abyss/models/Actors/utils/ActorUtils.hpp>

namespace abyss::LaunShark::Shot
{
    WaitState::WaitState()
    {}
    void WaitState::start()
    {
        m_timer = ActorUtils::CreateTimer(*m_pActor, ShotParam::Wait::Time);
    }
    void WaitState::update(double dt)
    {
        m_body->setVelocity(m_rotate->getDir9() * ShotParam::Wait::Speed);
        m_body->update(dt);
        if (m_timer.reachedZero()) {
            this->changeState(State::Pursuit);
        }
    }
    void WaitState::draw() const
    {
        this->m_pActor->getBindedView()->drawWait();
    }

}
