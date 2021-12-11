#include "StabPrevState.hpp"
#include <abyss/utils/Coro/Wait/Wait.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
	void StabPrevState::start()
	{
		m_behavior->setActive(false);
	}
	void StabPrevState::end()
	{
	}
	Coro::Task<> StabPrevState::task()
	{
		m_shake->request(3.0, 1.0);

		co_await Coro::WaitWhile([&] {
			return m_shake->isShakeing();
		});

		co_return;
	}
}
