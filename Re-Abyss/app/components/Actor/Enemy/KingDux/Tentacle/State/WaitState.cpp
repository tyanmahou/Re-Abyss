#include "WaitState.hpp"


namespace abyss::Actor::Enemy::KingDux::Tentacle
{
	void WaitState::start()
	{
		m_behavior->setActive(true);
	}
}
