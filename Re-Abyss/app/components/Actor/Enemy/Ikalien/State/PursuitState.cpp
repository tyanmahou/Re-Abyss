#include <abyss/components/Actor/Enemy/Ikalien/State/PursuitState.hpp>
#include <abyss/components/Actor/Enemy/Ikalien/State/SwimState.hpp>

#include <abyss/params/Actor/Enemy/Ikalien/Param.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <Siv3D.hpp>
namespace abyss::Actor::Enemy::Ikalien
{
    PursuitState::PursuitState():
        m_timer(2.0)
    {}
    void PursuitState::start()
    {
        m_body->noneResistanced();
        m_motion->set(Motion::Pursuit);
    }
    void PursuitState::update()
    {
        auto dt = m_pActor->deltaTime();

        s3d::Vec2 d = ActorUtils::ToPlayer(*m_pActor, *m_body);
        const double speed = s3d::Math::ToRadians(Param::Pursuit::RotateDeg);
        double rotate = m_rotate->getRotate();
        if (m_rotate->getDir().cross(d) > 0) {
            rotate +=  speed * dt;
        } else {
            rotate -= speed * dt;
        }
        m_rotate->setRotate(rotate);

        Vec2 nextOffset = Mat3x2::Rotate(rotate).transformPoint(Param::Base::Pivot);
        m_body->setOffset(nextOffset);

        m_body->setVelocity(m_rotate->getDir() * Param::Pursuit::Speed);
        m_timer.update(dt);
        if (m_timer.isEnd()) {
            this->changeState<SwimState>();
        }
    }
}
