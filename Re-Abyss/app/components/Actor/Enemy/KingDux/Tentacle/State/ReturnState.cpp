#include "ReturnState.hpp"
#include <abyss/utils/TimeLite/Timer.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
	void ReturnState::start()
	{
	}
	Coro::Task<> ReturnState::task()
	{
		TimeLite::Timer moveTimer{ 1.0 };
		Vec2 startPos = m_body->getPos();
		Vec2 endPos = startPos + m_rotate->getDir9() * -1000.0;

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
		// 破棄
		m_pActor->destroy();
	}
}
