#include <abyss/components/Actor/Enemy/KingDux/State/DanceState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/WaitState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/KingDuxUtil.hpp>
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
		// 少し待ってから
		co_await BehaviorUtil::WaitForSeconds(m_pActor, 1.5s);

		// BabyDuxを生成
		KingDuxUtil::BuildBaby(m_pActor, BabyDuxParam::Convene::Baby);

		co_await BehaviorUtil::WaitForSeconds(m_pActor, 1.0s);

		this->changeState<WaitState>();
		co_return;
	}

	void DanceState::update()
	{
	}
}
