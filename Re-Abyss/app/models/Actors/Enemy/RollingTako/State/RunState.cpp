#include "RunState.hpp"
#include <abyss/params/Actors/Enemy/RollingTako/Param.hpp>
namespace abyss::RollingTako
{
    void RunState::start()
    {
        m_draw->request(DrawModel::Kind::Run);
    }
    void RunState::update([[maybe_unused]] double dt)
    {
        if (m_body->isForward(Forward::Left)) {
            m_body->setAccelX(-Param::Run::AccelX);
        } else if (m_body->isForward(Forward::Right)) {
            m_body->setAccelX(Param::Run::AccelX);
        }
    }
}
