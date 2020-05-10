#include "RunState.hpp"
#include <abyss/views/Actors/RollingTako/RollingTakoVM.hpp>
#include <abyss/params/Actors/RollingTako/Param.hpp>
namespace abyss::RollingTako
{
    void RunState::update(double dt)
    {
        if (m_body->isForward(Forward::Left)) {
            m_body->setAccelX(-Param::Run::AccelX);
        } else if (m_body->isForward(Forward::Right)) {
            m_body->setAccelX(Param::Run::AccelX);
        }
        BaseState::update(dt);
    }

    void RunState::draw() const
    {
        m_pActor->getBindedView()->drawRun();
    }
}
