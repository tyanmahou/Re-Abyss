#include <abyss/components/Actor/Enemy/KingDux/State/DanceState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/WaitState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/KingDuxUtil.hpp>
#include <abyss/components/Actor/Enemy/KingDux/BabyCtrl.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
	void DanceState::start()
	{
		m_modelUpdater->setTimeScale(4.0);
		m_eyeCtrl->setDanceMode();
	}

	void DanceState::end()
	{
		m_modelUpdater->setTimeScale(1.0);
	}

	Coro::Fiber<> DanceState::updateAsync()
	{
		auto babyCtrl = m_pActor->find<BabyCtrl>();
		for (const auto& desc : KingDux::BabyDuxParam::Convene::Baby) {
			// 少し待ってから
			co_await BehaviorUtil::WaitForSeconds(m_pActor, desc.waitTimeSec);

			// BabyDuxを生成
			auto baby = KingDuxUtil::BuildBaby(m_pActor, desc);
			babyCtrl->add(baby);
		}

		co_await BehaviorUtil::WaitForSeconds(m_pActor, 0.5s);

		this->changeState<WaitState>();
		co_return;
	}

	void DanceState::update()
	{
	}
}
