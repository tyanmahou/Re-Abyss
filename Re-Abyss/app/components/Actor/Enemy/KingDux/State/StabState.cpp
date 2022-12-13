#include <abyss/components/Actor/Enemy/KingDux/State/StabState.hpp>

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
		for (const auto& desc : m_tentacleDesc) {
			m_tentacles << KingDuxUtil::BuildTentacle(m_pActor, desc);
		}
	}
	void StabState::end()
	{
		KingDuxUtil::RequestRetires(m_tentacles);
	}
	Fiber<void> StabState::task()
	{
		co_await KingDuxUtil::WaitTillStabAction(m_pActor, m_tentacles);

		this->changeState<WaitState>();
		co_return;
	}
}
