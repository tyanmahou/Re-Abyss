#include "WaitState.hpp"


namespace abyss::Actor::Enemy::KingDux
{
	void WaitState::start()
	{
		m_behavior->setActive(true);
	}
}
