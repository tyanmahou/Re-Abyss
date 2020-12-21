#include "WaitState.hpp"
#include "AttackPlusState.hpp"

#include <abyss/params/Actors/Enemy/Schield/Param.hpp>
#include <abyss/components/Actors/utils/ActorUtils.hpp>
#include <abyss/modules/System/System.hpp>
#include <abyss/components/Actors/Commons/ActorTime.hpp>

namespace abyss::Actor::Enemy::Schield
{
    WaitState::WaitState()
    {}
    Task<> WaitState::start()
    {
        m_timer = ActorUtils::CreateTimer(*m_pActor, Param::Wait::TimeSec);
        m_pActor->find<ActorTime>()->resetDrawTime();

        m_face->on();
        co_return;
    }
    void WaitState::update()
    {
        if (m_timer.reachedZero() && m_pActor->getModule<Camera>()->inScreen(m_body->getPos())) {
            this->changeState<AttackPlusState>();
        }
    }
    void WaitState::end()
    {
        m_face->off();
    }
    void WaitState::draw() const
    {
        (*m_view)->drawWait();
    }
}
