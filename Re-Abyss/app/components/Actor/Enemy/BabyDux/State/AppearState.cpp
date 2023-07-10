#include <abyss/components/Actor/Enemy/BabyDux/State/AppearState.hpp>
#include <abyss/components/Actor/Enemy/BabyDux/State/MoveState.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::BabyDux
{
	void AppearState::start()
	{

	}
	Fiber<> AppearState::updateAsync()
	{
		// 移動
		{
			// 目標の位置を計算
			const Vec2 initPos = m_body->getPos();
			const Vec2& moveOffset = m_main->getAppearMove();
			const Vec2 targetPos = initPos + moveOffset;

			TimeLite::Timer timer(m_main->getAppearTime());
			while (!timer.isEnd())
			{
				timer.update(m_pActor->deltaTime());

				auto rate = timer.rate();
				rate = s3d::EaseOutBack(rate);
				auto newPos = s3d::Math::Lerp(initPos, targetPos, rate);
				m_body->moveToPos(newPos, m_pActor->deltaTime());
				co_yield{};
			}
		}

		this->changeState<MoveState>();
		co_return;
	}
}
