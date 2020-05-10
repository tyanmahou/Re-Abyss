#include "WaitState.hpp"

#include <abyss/models/Actors/utils/ActorUtils.hpp>
#include <abyss/views/Actors/RollingTako/RollingTakoVM.hpp>
#include <abyss/params/Actors/RollingTako/Param.hpp>

namespace abyss::RollingTako
{
    void WaitState::update(double dt)
    {
        s3d::Vec2 d = ActorUtils::PlayerDiffVec(*m_pActor, *m_body);
        double f = m_body->isForward(Forward::Right) ? 1.0 : -1.0;
        if (f * d.x > 0 && d.length() <= Param::Wait::SearchRange) {
            this->changeState(State::Run);
        }
        BaseState::update(dt);
    }

    void WaitState::draw() const
    {
        m_pActor->getBindedView()->drawWait();
    }
}
