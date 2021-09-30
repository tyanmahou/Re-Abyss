#include "WaitState.hpp"
#include "AttackPlusState.hpp"

#include <abyss/params/Actor/Enemy/Schield/Param.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/components/Common/ClockCtrl.hpp>

namespace abyss::Actor::Enemy::Schield
{
    WaitState::WaitState():
        m_timer(Param::Wait::TimeSec)
    {}
    void WaitState::start()
    {
        m_motion->set(Motion::Wait);

        m_pActor->find<ClockCtrl>()->resetDrawTime();

        m_face->on();
    }
    void WaitState::update()
    {
        m_timer.update(m_pActor->deltaTime());
        if (m_timer.isEnd() && m_pActor->getModule<Camera>()->inScreen(m_body->getPos())) {
            this->changeState<AttackPlusState>();
        }
    }
    void WaitState::end()
    {
        m_face->off();
    }
}
