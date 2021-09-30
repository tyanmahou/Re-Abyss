#include "PursuitEndState.hpp"
#include <abyss/params/Actor/Enemy/CodeZero/ShotParam.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    PursuitEndState::PursuitEndState():
        m_timer(ShotParam::Pursuit::EndToDeadTimeSec)
    {}

    void PursuitEndState::start()
    {
    }
    void PursuitEndState::update()
    {
        m_timer.update(m_pActor->deltaTime());
        if (m_timer.isEnd()) {
            m_pActor->destroy();
        }
    }
}
