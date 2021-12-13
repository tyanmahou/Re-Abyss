#include "StabState.hpp"
#include <abyss/utils/Coro/Wait/Wait.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
	void StabState::start()
	{
		m_behavior->setActive(false);
	}
	void StabState::end()
	{
	}
	Coro::Task<> StabState::task()
	{
		TimeLite::Timer moveTimer{ 1.5 };
		while (true) {
			double dt = m_pActor->deltaTime();
			moveTimer.update(dt);
			m_body->setVelocity(m_rotate->getDir9() * 400.0);
			if (moveTimer.isEnd()) {
				break;
			}
			co_yield{};
		}
		m_body
			->noneResistanced()
			.setVelocity(s3d::Vec2::Zero());
		co_return;
	}
}
