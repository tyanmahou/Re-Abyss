#include "StabState.hpp"

#include <abyss/components/Actor/Enemy/KingDux/KingDuxUtil.hpp>
#include <abyss/utils/Coro/Wait/Wait.hpp>

namespace abyss::Actor::Enemy::KingDux
{
	void StabState::start()
	{
		m_behavior->setActive(false);
		m_tentacles << KingDuxUtil::BuildTentacle(m_pActor, Param::Stab::Tentacle1);
		m_tentacles << KingDuxUtil::BuildTentacle(m_pActor, Param::Stab::Tentacle2);
	}
	Task<void> StabState::task()
	{
		co_await Coro::WaitUntil([&] {
			return m_tentacles.all([](const Ref<ActorObj>& obj) {
				return !obj;
			});
		});
		co_return;
	}
}
