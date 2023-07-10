#include <abyss/components/Actor/Enemy/CodeZero/State/DeadState.hpp>

#include <abyss/modules/Sfx/SpecialEffects.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Adv/Adventures.hpp>
#include <abyss/components/Actor/utils/StatePriority.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
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
        // 地震
        m_pActor->getModule<Camera>()->startQuake(5.0, 0.5);

		// 当たりむこう
		m_pActor->find<ColCtrl>()->setActive(false);

		m_head->setActive(false);
        m_wing->startDead();

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
	Coro::Fiber<> DeadState::updateAsync()
	{
		if (auto signalCtrl = m_pActor->getModule<Adventures>()->find<Adv::CodeZeroDemo::SignalCtrl>()) {
			co_await this->onEvent(signalCtrl);
		} else {
			co_await this->commonDead();
		}

		co_return;
	}
	void DeadState::update()
	{
	}

	Fiber<> DeadState::onEvent(Ref<Adv::CodeZeroDemo::SignalCtrl> signalCtrl)
	{
        signalCtrl->requestBattleEnd();
        // スローモーション
        co_await BehaviorUtil::GlobalSlowmotion(m_pActor, 2.5s);

		while (!signalCtrl->isRequestedDead()) {
			co_yield{};
		}
		co_await this->commonDead();
        if (auto&& hand = m_parts->getLeftHand()) {
            hand->destroy();
        }
        if (auto&& hand = m_parts->getRightHand()) {
            hand->destroy();
        }
        signalCtrl->setDeadEnd();
	}

	Fiber<> DeadState::commonDead()
	{
		co_await BossUtil::DeadDemo(m_pActor);
	}
}
