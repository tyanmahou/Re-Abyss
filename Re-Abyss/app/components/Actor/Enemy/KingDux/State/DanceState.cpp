#include <abyss/components/Actor/Enemy/KingDux/State/DanceState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/ConveneState.hpp>

#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
	void DanceState::start()
	{
		m_behavior->setActive(false);
		m_modelUpdater->setTimeScale(4.0);
		m_eyeCtrl->setDanceMode();
	}

	void DanceState::end()
	{
		m_modelUpdater->setTimeScale(1.0);
	}

	Coro::Task<> DanceState::task()
	{
		co_await BehaviorUtil::WaitForSeconds(m_pActor, 3.0s);
		this->changeState<ConveneState>();
		co_return;
	}

	void DanceState::update()
	{
	}
}
