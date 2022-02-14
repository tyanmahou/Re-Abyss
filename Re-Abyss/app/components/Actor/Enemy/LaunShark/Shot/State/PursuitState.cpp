#include <abyss/components/Actor/Enemy/LaunShark/Shot/State/PursuitState.hpp>
#include <abyss/components/Actor/Enemy/LaunShark/Shot/State/FiringedState.hpp>

#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/params/Actor/Enemy/LaunShark/ShotParam.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::LaunShark::Shot
{
    PursuitState::PursuitState():
        m_timer(ShotParam::Pursuit::Time)
    {}

    void PursuitState::start()
    {
        m_motion->set(Motion::Firinged);
    }
    void PursuitState::update()
    {
        auto dt = m_pActor->deltaTime();

        s3d::Vec2 d = ActorUtils::ToPlayer(*m_pActor, *m_body);
        const double speed = s3d::Math::ToRadians(ShotParam::Pursuit::RotateDeg);
        double rotate = m_rotate->getRotate();
        if (m_rotate->getDir9().cross(d) > 0) {
            rotate += speed * dt;
        } else {
            rotate -= speed * dt;
        }
        m_rotate->setRotate(rotate);
        m_body->setVelocity(m_rotate->getDir9() * ShotParam::Pursuit::Speed);

        m_timer.update(dt);
        if (m_timer.isEnd()) {
            this->changeState<FiringedState>();
        }
    }
}
