#include "StabState.hpp"

#include <abyss/components/Actor/Enemy/KingDux/KingDuxUtil.hpp>

namespace abyss::Actor::Enemy::KingDux
{
	void StabState::start()
	{
		m_behavior->setActive(false);
		KindDuxUtil::BuildTentacle(m_pActor, Param::Stab::Tentacle1);
		KindDuxUtil::BuildTentacle(m_pActor, Param::Stab::Tentacle2);
	}
	Task<void> StabState::task()
	{
		co_return;
	}
}
