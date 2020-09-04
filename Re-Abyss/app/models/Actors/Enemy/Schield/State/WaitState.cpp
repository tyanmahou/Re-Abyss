#include "WaitState.hpp"
#include "AttackPlusState.hpp"

#include <abyss/params/Actors/Enemy/Schield/Param.hpp>
#include <abyss/models/Actors/utils/ActorUtils.hpp>
#include <abyss/controllers/System/System.hpp>
#include <abyss/models/Actors/Commons/ActorTimeModel.hpp>

namespace abyss::Actor::Schield
{
    WaitState::WaitState()
    {}
    void WaitState::start()
    {
        m_timer = ActorUtils::CreateTimer(*m_pActor, Param::Wait::TimeSec);
        m_pActor->find<ActorTimeModel>()->resetDrawTime();

        m_face->on();
    }
    void WaitState::update([[maybe_unused]]double dt)
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
