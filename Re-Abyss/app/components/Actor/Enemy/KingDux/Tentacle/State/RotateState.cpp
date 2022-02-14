#include <abyss/components/Actor/Enemy/KingDux/Tentacle/State/RotateState.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
	void RotateState::start()
	{
	}
	void RotateState::update()
	{
        auto dt = m_pActor->deltaTime();

        s3d::Vec2 d = ActorUtils::ToPlayer(*m_pActor, *m_body);
        const double speed = s3d::Math::ToRadians(5.0);
        double rotate = m_rotate->getRotate();
        const double angle = m_rotate->getDir9().getAngle(d);
        
        const double rotateDelta = speed * dt;
        const double fixRotateDelta = s3d::Min(rotateDelta, s3d::Abs(angle));
        if (m_rotate->getDir9().cross(d) > 0) {
            rotate += fixRotateDelta;
        } else {
            rotate -= fixRotateDelta;
        }
        m_rotate->setRotate(rotate);
	}
}
