#include "RollingTakoWaitState.hpp"

#include <abyss/controllers/Actors/utils/ActorUtils.hpp>
#include <abyss/views/Actors/RollingTako/RollingTakoVM.hpp>
#include <abyss/params/Actors/RollingTako/RollingTakoParam.hpp>

namespace abyss
{
    void RollingTakoWaitState::update(double dt)
    {
        s3d::Vec2 d = ActorUtils::PlayerDiffVec(*m_actor, *m_body);
        double f = m_body->isForward(Forward::Right) ? 1.0 : -1.0;
        if (f * d.x > 0 && d.length() <= RollingTakoParam::Wait::SearchRange) {
            this->changeState(RollingTakoActor::Run);
        }
        RollingTakoBaseState::update(dt);
    }

    void RollingTakoWaitState::draw() const
    {
        m_actor->getBindedView()->drawWait();
    }
}
