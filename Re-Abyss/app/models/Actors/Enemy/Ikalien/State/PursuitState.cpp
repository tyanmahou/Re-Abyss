#include "PursuitState.hpp"

#include <abyss/views/Actors/Enemy/Ikalien/IkalienVM.hpp>
#include <abyss/params/Actors/Enemy/Ikalien/Param.hpp>
#include <abyss/models/Actors/utils/ActorUtils.hpp>
#include <Siv3D.hpp>
namespace abyss::Ikalien
{
    PursuitState::PursuitState()
    {}
    void PursuitState::start()
    {
        m_timer = ActorUtils::CreateTimer(*m_pActor, 2.0);
        m_body->noneResistanced();
    }
    void PursuitState::update(double dt)
    {
        s3d::Vec2 d = ActorUtils::PlayerDiffVec(*m_pActor, *m_body);
        const double speed = s3d::Math::ToRadians(Param::Pursuit::RotateDeg);
        double rotate = m_rotate->getRotate();
        if (m_rotate->getDir().cross(d) > 0) {
            rotate +=  speed * dt;
        } else {
            rotate -= speed * dt;
        }
        m_rotate->setRotate(rotate);

        Vec2 nextPivot = Mat3x2::Rotate(rotate).transform(Param::Base::Pivot);
        m_body->setPivot(nextPivot);

        m_body->setVelocity(m_rotate->getDir() * Param::Pursuit::Speed);
        m_body->update(dt);
        if (m_timer.reachedZero()) {
            this->changeState(State::Swim);
        }
    }
    void PursuitState::draw() const
    {
        m_pActor->getBindedView()->drawPursuit();
    }

}
