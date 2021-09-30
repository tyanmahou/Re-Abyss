#include "WaitState.hpp"
#include "PursuitState.hpp"

#include <abyss/params/Actor/Enemy/LaunShark/ShotParam.hpp>

namespace abyss::Actor::Enemy::LaunShark::Shot
{
    WaitState::WaitState():
        m_timer(ShotParam::Wait::Time)
    {}
    void WaitState::start()
    {
        m_motion->set(Motion::Wait);
        m_body->noneResistanced();
    }
    void WaitState::update()
    {
        m_timer.update(m_pActor->deltaTime());
        m_body->setVelocity(m_rotate->getDir9() * ShotParam::Wait::Speed);
        if (m_timer.isEnd()) {
            this->changeState<PursuitState>();
        }
    }
}
