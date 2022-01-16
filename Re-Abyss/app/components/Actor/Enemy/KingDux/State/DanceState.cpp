#include "DanceState.hpp"
#include "WaitState.hpp"

#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
	void DanceState::start()
	{
		m_behavior->setActive(false);
	}

	Coro::Task<> DanceState::task()
	{
		co_await BehaviorUtil::WaitForSeconds(m_pActor, 1.0s);
		this->changeState<WaitState>();
		co_return;
	}

	void DanceState::update()
	{
	}
}
