#include "PursuitState.hpp"
#include <abyss/models/Actors/utils/ActorUtils.hpp>

#include <abyss/params/Actors/LaunShark/ShotParam.hpp>

#include <Siv3D.hpp>

namespace abyss::LaunShark::Shot
{
    PursuitState::PursuitState()
    {}

    void PursuitState::start()
    {
        m_timer = ActorUtils::CreateTimer(*m_pActor, ShotParam::Pursuit::Time);
    }
    void PursuitState::update(double dt)
    {
        s3d::Vec2 d = ActorUtils::PlayerDiffVec(*m_pActor, *m_body);
        const double speed = s3d::Math::ToRadians(ShotParam::Pursuit::RotateDeg);
        double rotate = m_rotate->getRotate();
        if (m_rotate->getDir9().cross(d) > 0) {
            rotate += speed * dt;
        } else {
            rotate -= speed * dt;
        }
        m_rotate->setRotate(rotate);
        m_body->setVelocity(m_rotate->getDir9() * ShotParam::Pursuit::Speed);
        m_body->update(dt);
        if (m_timer.reachedZero()) {
            this->changeState(State::Firinged);
        }
    }

    void PursuitState::draw() const
    {
        m_pActor->getBindedView()->drawFiringed();
    }

}
