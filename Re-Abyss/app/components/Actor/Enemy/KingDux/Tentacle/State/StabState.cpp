#include "StabState.hpp"
#include <abyss/utils/Coro/Wait/Wait.hpp>

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
		co_return;
	}
}
