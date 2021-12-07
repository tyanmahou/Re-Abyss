#include "RotateState.hpp"
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

        s3d::Vec2 d = ActorUtils::PlayerDiffVec(*m_pActor, *m_body);
        const double speed = s3d::Math::ToRadians(60.0);
        double rotate = m_rotate->getRotate();
        if (m_rotate->getDir().cross(d) > 0) {
            rotate += speed * dt;
        } else {
            rotate -= speed * dt;
        }
	}
}
