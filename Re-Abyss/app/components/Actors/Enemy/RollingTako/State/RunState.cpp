#include "RunState.hpp"
#include <abyss/params/Actors/Enemy/RollingTako/Param.hpp>
namespace abyss::Actor::Enemy::RollingTako
{
    void RunState::start()
    {
    }
    void RunState::update()
    {
        if (m_body->isForward(Forward::Left)) {
            m_body->setAccelX(-Param::Run::AccelX);
        } else if (m_body->isForward(Forward::Right)) {
            m_body->setAccelX(Param::Run::AccelX);
        }
    }

    void RunState::draw() const
    {
        (*m_view)->drawRun();
    }
}
