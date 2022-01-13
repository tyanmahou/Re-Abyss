#include "StabState.hpp"

#include <abyss/components/Actor/Enemy/KingDux/KingDuxUtil.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/WaitState.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
	StabState::StabState(const s3d::Array<TentacleDesc>& desc):
		m_tentacleDesc(desc)
	{}
	void StabState::start()
	{
		m_behavior->setActive(false);
		for (const auto& desc : m_tentacleDesc) {
			m_tentacles << KingDuxUtil::BuildTentacle(m_pActor, desc);
		}
	}
	Task<void> StabState::task()
	{
		co_await KingDuxUtil::WaitTillStabAction(m_pActor, m_tentacles);

		this->changeState<WaitState>();
		co_return;
	}
}
