#include "WaitState.hpp"
#include "RunState.hpp"

#include <abyss/models/Actors/utils/ActorUtils.hpp>
#include <abyss/params/Actors/Enemy/RollingTako/Param.hpp>

namespace abyss::RollingTako
{
    void WaitState::start()
    {
        m_draw->request(DrawModel::Kind::Wait);
    }

    void WaitState::update(double dt)
    {
        s3d::Vec2 d = ActorUtils::PlayerDiffVec(*m_pActor, *m_body);
        double f = m_body->isForward(Forward::Right) ? 1.0 : -1.0;
        if (f * d.x > 0 && d.length() <= Param::Wait::SearchRange) {
            this->changeState<RunState>();
        }
    }
}
