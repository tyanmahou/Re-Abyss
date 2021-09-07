#include "RunState.hpp"
#include <abyss/params/Actor/Enemy/RollingTako/Param.hpp>
namespace abyss::Actor::Enemy::RollingTako
{
    void RunState::start()
    {
        m_motion->set(Motion::Run);
    }
    void RunState::update()
    {
        if (m_body->isForward(Forward::Left)) {
            m_body->setAccelX(-Param::Run::AccelX);
        } else if (m_body->isForward(Forward::Right)) {
            m_body->setAccelX(Param::Run::AccelX);
        }
    }
}
