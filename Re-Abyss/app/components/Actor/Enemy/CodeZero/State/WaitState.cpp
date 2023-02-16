#include <abyss/components/Actor/Enemy/CodeZero/State/WaitState.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
	void WaitState::start()
	{
		m_behavior->setActiveBehavior(true);
        m_wing->startWait();
	}
}
