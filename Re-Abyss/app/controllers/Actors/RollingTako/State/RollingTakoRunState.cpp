#include "RollingTakoRunState.hpp"
#include <abyss/views/Actors/RollingTako/RollingTakoVM.hpp>
#include <abyss/params/Actors/RollingTako/RollingTakoParam.hpp>
namespace abyss
{
    void RollingTakoRunState::update(double dt)
    {
        if (m_body->isForward(Forward::Left)) {
            m_body->setAccelX(-RollingTakoParam::Run::AccelX);
        } else if (m_body->isForward(Forward::Right)) {
            m_body->setAccelX(RollingTakoParam::Run::AccelX);
        }
        RollingTakoBaseState::update(dt);
    }

    void RollingTakoRunState::draw() const
    {
        m_actor->getBindedView()->drawRun();
    }
}
