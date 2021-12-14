#include "StabState.hpp"
#include <abyss/utils/Coro/Wait/Wait.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
#include <abyss/utils/Math/Math.hpp>

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
		Vec2 startPos = m_body->getPos();
		Vec2 endPos = startPos + m_rotate->getDir9() * 600.0;

		while (true) {
			double dt = m_pActor->deltaTime();
			moveTimer.update(dt);

			auto targetPos = s3d::Math::Lerp(startPos, endPos, moveTimer.rate());
			m_body->moveToPos(targetPos, dt);

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
