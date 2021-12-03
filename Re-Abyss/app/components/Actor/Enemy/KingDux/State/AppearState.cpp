#include "AppearState.hpp"
#include "WaitState.hpp"
#include <abyss/models/Camera/QuakeModel.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
	void AppearState::start()
	{
		m_behavior->setActive(false);
		m_quake = m_pActor->getModule<Camera>()->startQuake(5.0, 5.0);
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
		while (!moveTimer.isEnd()) {
			moveTimer.update(m_pActor->deltaTime());
			auto pos = s3d::Math::Lerp(initPos + Vec2{ 0, 800 }, initPos, moveTimer.rate());
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
