#include "AppearState.hpp"
#include "WaitState.hpp"
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Sfx/Flush/Flush.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Enemy/KingDux/KingDuxUtil.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
#include <abyss/utils/Coro/Wait/Wait.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
	void AppearState::start()
	{
		m_behavior->setActive(false);
		m_motion->set(Motion::Hide);
		m_pActor->find<VModel>()->setVisible(true);
	}
	void AppearState::end()
	{
		KingDuxUtil::SetVisible(m_pActor, true);
	}
	Coro::Task<> AppearState::task()
	{
		Vec2 initPos = m_body->getPos();
		const Vec2 offset = Vec2{ 0, 400 };
		m_body->setPos(initPos + offset);

		// Shake
		{
			co_await Coro::WaitForSeconds(0.5s);
			m_shake->request(10.0, 0.5);
			co_await Coro::WaitForSeconds(1.5s);
			m_shake->request(10.0, 0.5);
			co_await Coro::WaitForSeconds(1.0s);
		}

		// Flush
		{
			auto*const flush = m_pActor->getModule<Flush>();
			flush->start(0.5);

			co_await Coro::WaitUntil([=] {
				return flush->isFadeInEnd();
			});
		}
		KingDuxUtil::SetVisible(m_pActor, true);
		m_motion->set(Motion::Wait);
		constexpr double moveTimeSec = 2.5;
		m_pActor->getModule<Camera>()->startQuake(10, 0.3);
		TimeLite::Timer moveTimer{ moveTimeSec };
		while (!moveTimer.isEnd()) {
			moveTimer.update(m_pActor->deltaTime());
			double rate = EaseOutExpo(moveTimer.rate());
			auto pos = s3d::Math::Lerp(initPos + offset, initPos, rate);
			m_body->setPos(pos);
			co_yield{};
		}
		this->changeState<WaitState>();
		co_return;
	}
	void AppearState::update()
	{
	}
}
