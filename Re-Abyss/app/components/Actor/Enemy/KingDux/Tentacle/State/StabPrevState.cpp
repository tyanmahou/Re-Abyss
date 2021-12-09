#include "StabPrevState.hpp"

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
		co_return;
	}
}
