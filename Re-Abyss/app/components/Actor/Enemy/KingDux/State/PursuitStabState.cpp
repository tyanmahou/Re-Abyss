#include <abyss/components/Actor/Enemy/KingDux/State/PursuitStabState.hpp>

#include <abyss/components/Actor/Enemy/KingDux/KingDuxUtil.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/WaitState.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
	void PursuitStabState::start()
	{
		for (const auto& desc : TentacleParam::PursuitStab::Tentacle) {
			m_tentacles << KingDuxUtil::BuildTentacle(m_pActor, desc);
		}
	}
	void PursuitStabState::end()
	{
		KingDuxUtil::RequestRetires(m_tentacles);
	}
	Fiber<void> PursuitStabState::task()
	{
		co_await KingDuxUtil::WaitTillStabAction(m_pActor, m_tentacles);

		this->changeState<WaitState>();
		co_return;
	}
}
