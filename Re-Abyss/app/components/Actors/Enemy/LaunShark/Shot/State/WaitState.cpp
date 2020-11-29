#include "WaitState.hpp"
#include "PursuitState.hpp"

#include <abyss/params/Actors/Enemy/LaunShark/ShotParam.hpp>
#include <abyss/components/Actors/utils/ActorUtils.hpp>

namespace abyss::Actor::Enemy::LaunShark::Shot
{
    WaitState::WaitState()
    {}
    void WaitState::start()
    {
        m_body->noneResistanced();
        m_timer = ActorUtils::CreateTimer(*m_pActor, ShotParam::Wait::Time);
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
