#include <abyss/components/Actor/Enemy/CodeZero/State/DeadState.hpp>

#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Sfx/SpecialEffects.hpp>
#include <abyss/modules/Novel/Novels.hpp>

#include <abyss/components/Actor/utils/StatePriority.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Actor/Common/AudioSource.hpp>
#include <abyss/components/Effect/Actor/Common/EnemyDead/Builder.hpp>
#include <abyss/components/Effect/Common/BossFadeMask.hpp>
#include <abyss/utils/Coro/Task/Wait.hpp>

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
		if (auto signalCtrl = m_pActor->getModule<Novels>()->find<Novel::BossTalk0_1::SignalCtrl>()) {
			co_await this->onEvent(signalCtrl);
		} else {
			co_await this->commonDead();
		}

		co_return;
	}
	void DeadState::update()
	{
	}

	Task<> DeadState::onEvent(Ref<Novel::BossTalk0_1::SignalCtrl> signalCtrl)
	{
		while (!signalCtrl->isRequestedDead()) {
			co_yield{};
		}
		co_await this->commonDead();

		signalCtrl->setDeadEnd();
	}

	Task<> DeadState::commonDead()
	{
		co_await BehaviorUtil::WaitForSeconds(m_pActor, 1.0);
		// 爆発
		{
			// ボスフェード開始
			auto* bossFade = m_pActor->getModule<SpecialEffects>()->bossFade();
			bossFade->start();

			auto region = m_pActor->find<Body>()->region();

			for (int32 count : step(45)) {
				if (count == 4 || count == 5 || count == 11 || count == 12
				 || count == 18 || count == 19 || count == 25 || count == 26
					) {
					// 画面フラッシュ
					m_pActor->getModule<SpecialEffects>()->flush()->start(0.1);
				}
				auto effectPos = s3d::RandomVec2(region);
				auto effectObj = m_pActor->getModule<Effects>()->createWorldFront<Effect::Actor::EnemyDead::Builder>(effectPos);
				effectObj->attach<Effect::BossFadeMask>(effectObj.get());

				m_pActor->find<AudioSource>()->playAt(U"Damage", effectPos);

				co_await BehaviorUtil::WaitForSeconds(m_pActor, 0.2);
			}
			co_await Coro::WaitUntil([&] {
				return bossFade->isFadeOutEnd();
			});
		}
		m_pActor->destroy();
	}
}
