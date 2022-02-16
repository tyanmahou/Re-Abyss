#include <abyss/components/Actor/Enemy/KingDux/Tentacle/State/WaitState.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
	void WaitState::start()
	{
		m_behavior->setActiveBehavior(true);
	}
}
