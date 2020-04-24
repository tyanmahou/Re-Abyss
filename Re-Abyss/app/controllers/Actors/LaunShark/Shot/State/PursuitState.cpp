#include "PursuitState.hpp"
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/Actors/utils/ActorUtils.hpp>

#include <abyss/params/Actors/LaunShark/ShotParam.hpp>

#include <Siv3D.hpp>

namespace abyss::LaunShark::Shot
{
    PursuitState::PursuitState() :
        m_timer(ShotParam::Pursuit::Time, true, WorldTime::TimeMicroSec)
    {}

    void PursuitState::update(double dt)
    {
        s3d::Vec2 d = ActorUtils::PlayerDiffVec(*m_actor, *m_body);
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
        this->m_actor->getBindedView()->drawFiringed();
    }

}
