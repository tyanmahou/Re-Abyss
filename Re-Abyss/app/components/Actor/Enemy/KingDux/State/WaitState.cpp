#include <abyss/components/Actor/Enemy/KingDux/State/WaitState.hpp>

#include <abyss/components/Actor/Enemy/KingDux/KingDuxUtil.hpp>

namespace abyss::Actor::Enemy::KingDux
{
	void WaitState::start()
	{
		KingDuxUtil::SetVisible(m_pActor, true);
		m_behavior->setActiveBehavior(true);
	}
}
