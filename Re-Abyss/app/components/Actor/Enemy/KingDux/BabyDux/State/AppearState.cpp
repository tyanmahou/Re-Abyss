#include <abyss/components/Actor/Enemy/KingDux/BabyDux/State/AppearState.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
	void AppearState::start()
	{

	}
	Task<> AppearState::task()
	{
		// 移動
		{
			// 目標の高さ
			const double targetY = m_main->parentPos().y + 400;
			const Vec2 initPos = m_body->getPos();
			const Vec2 targetPos = Vec2{ initPos.x, targetY };

			TimeLite::Timer timer(2.0);
			while (!timer.isEnd())
			{
				timer.update(m_pActor->deltaTime());

				auto rate = timer.rate();
				auto newPos = s3d::Math::Lerp(initPos, targetPos, rate);
				m_body->moveToPos(newPos, m_pActor->deltaTime());
				co_yield{};
			}
		}
		co_return;
	}
}