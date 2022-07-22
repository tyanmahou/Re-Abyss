#include <abyss/components/Actor/Enemy/CodeZero/State/DeadState.hpp>

#include <abyss/modules/Sfx/SpecialEffects.hpp>
#include <abyss/modules/Novel/Novels.hpp>

#include <abyss/components/Actor/utils/StatePriority.hpp>
#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Actor/Enemy/BossUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
	void DeadState::Change(ActorObj* pActor)
	{
		pActor->find<StateCtrl>()->changeState<DeadState, StatePriority::Dead>();
	}
	void DeadState::start()
	{
		// 画面フラッシュ
		m_pActor->getModule<SpecialEffects>()->flush()->start(0, 0.5);

		// 当たりむこう
		m_pActor->find<ColCtrl>()->setActive(false);

		m_head->setActive(false);

		// 手も死亡
		if (auto&& hand = m_parts->getLeftHand()) {
			hand->dead();
		}
		if (auto&& hand = m_parts->getRightHand()) {
			hand->dead();
		}
	}
	void DeadState::end()
	{
	}
	Coro::Task<> DeadState::task()
	{
		if (auto signalCtrl = m_pActor->getModule<Novels>()->find<Novel::CodeZeroDemo::SignalCtrl>()) {
			co_await this->onEvent(signalCtrl);
		} else {
			co_await this->commonDead();
		}

		co_return;
	}
	void DeadState::update()
	{
	}

	Task<> DeadState::onEvent(Ref<Novel::CodeZeroDemo::SignalCtrl> signalCtrl)
	{
        signalCtrl->requestBattleEnd();

		while (!signalCtrl->isRequestedDead()) {
			co_yield{};
		}
		co_await this->commonDead();

		signalCtrl->setDeadEnd();
	}

	Task<> DeadState::commonDead()
	{
		co_await BossUtil::DeadDemo(m_pActor);
	}
}
