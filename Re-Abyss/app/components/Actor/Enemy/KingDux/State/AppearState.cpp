#include "AppearState.hpp"
#include "WaitState.hpp"
#include <abyss/models/Camera/QuakeModel.hpp>
#include <abyss/modules/Sfx/Flush/Flush.hpp>
#include <abyss/components/Actor/Enemy/KingDux/KingDuxUtil.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
#include <abyss/utils/Coro/Wait/Wait.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
	void AppearState::start()
	{
		m_behavior->setActive(false);
		KingDuxUtil::SetVisible(m_pActor, true);
	}
	void AppearState::end()
	{
		if (m_quake) {
			m_quake->stop();
		}
	}
	Coro::Task<> AppearState::task()
	{
		Vec2 initPos = m_body->getPos();
		TimeLite::Timer moveTimer{5.0};
		const Vec2 offset = Vec2{ 0, 400 };
		m_body->setPos(initPos + offset);

		co_await Coro::WaitForSeconds(1s);
		{
			auto*const flush = m_pActor->getModule<Flush>();
			flush->start(0.5);

			co_await Coro::WaitUntil([=] {
				return flush->isFadeInEnd();
			});
		}
		m_quake = m_pActor->getModule<Camera>()->startQuake(5.0, 5.0);
		while (!moveTimer.isEnd()) {
			moveTimer.update(m_pActor->deltaTime());
			auto pos = s3d::Math::Lerp(initPos + offset, initPos, moveTimer.rate());
			m_body->setPos(pos);
			co_yield{};
		}
		m_pActor->getModule<Camera>()->startQuake(10, 0.3);
		this->changeState<WaitState>();
		co_return;
	}
	void AppearState::update()
	{
	}
}
