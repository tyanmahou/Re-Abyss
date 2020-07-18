#include "StartState.hpp"
#include "WaitState.hpp"
#include <abyss/params/Actors/Enemy/LaunShark/ShotParam.hpp>
namespace abyss::LaunShark::Shot
{
    void StartState::start()
    {
        m_body->setVelocity(m_rotate->getDir9() * ShotParam::Start::Speed);
        m_body->setAccel(-m_rotate->getDir9() * ShotParam::Start::Decel);

        m_draw->request(DrawModel::Kind::Wait);
    }

    void StartState::update([[maybe_unused]]double dt)
    {
        if (m_body->getVelocity().length() <= 30) {
            this->changeState<WaitState>();
        }
    }

}
