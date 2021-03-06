#include "WaitState.hpp"
#include "RunState.hpp"

#include <abyss/components/Actors/utils/ActorUtils.hpp>
#include <abyss/params/Actors/Enemy/RollingTako/Param.hpp>

namespace abyss::Actor::Enemy::RollingTako
{
    Task<> WaitState::start()
    {
        co_return;
    }

    void WaitState::update()
    {
        s3d::Vec2 d = ActorUtils::PlayerDiffVec(*m_pActor, *m_body);
        double f = m_body->isForward(Forward::Right) ? 1.0 : -1.0;
        if (f * d.x > 0 && d.length() <= Param::Wait::SearchRange) {
            this->changeState<RunState>();
        }
    }

    void WaitState::draw()const
    {
        (*m_view)->drawWait();
    }
}
