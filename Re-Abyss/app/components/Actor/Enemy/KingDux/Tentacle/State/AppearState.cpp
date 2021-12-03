#include "AppearState.hpp"

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
	void AppearState::start()
	{
	}
	void AppearState::update()
	{
		if (m_moveTimer.isEnd()) {
			m_body
				->noneResistanced()
				.setVelocity(s3d::Vec2::Zero());
			return;
		}
		double dt = m_pActor->deltaTime();
		m_moveTimer.update(dt);
		m_body->setVelocity(m_rotate->getDir9() * 80.0);
	}
}
