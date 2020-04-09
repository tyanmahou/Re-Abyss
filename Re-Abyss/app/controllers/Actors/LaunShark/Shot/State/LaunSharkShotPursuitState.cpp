#include "LaunSharkShotPursuitState.hpp"
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/World/World.hpp>

#include <abyss/params/Actors/LaunShark/LaunSharkShotParam.hpp>

#include <Siv3D.hpp>

namespace abyss
{
    LaunSharkShotPursuitState::LaunSharkShotPursuitState() :
        m_timer(LaunSharkShotParam::Pursuit::Time, true, WorldTime::TimeMicroSec)
    {}

    void LaunSharkShotPursuitState::update(double dt)
    {
        s3d::Vec2 d = m_actor->getWorld()->getPlayerPos() - m_body->getPos();
        const double speed = s3d::Math::ToRadians(LaunSharkShotParam::Pursuit::RotateDeg);
        double rotate = m_rotate->getRotate();
        if (m_rotate->getDir9().cross(d) > 0) {
            rotate += speed * dt;
        } else {
            rotate -= speed * dt;
        }
        m_rotate->setRotate(rotate);
        m_body->setVelocity(m_rotate->getDir9() * LaunSharkShotParam::Pursuit::Speed);
        m_body->update(dt);
        if (m_timer.reachedZero()) {
            this->changeState(LaunSharkShotActor::State::Firinged);
        }
    }

    void LaunSharkShotPursuitState::draw() const
    {
        this->m_actor->getBindedView()->drawFiringed();
    }

}
