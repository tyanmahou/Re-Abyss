#include <abyss/components/Actor/Enemy/CodeZero/State/DeadState.hpp>

#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Sfx/Flush/Flush.hpp>

#include <abyss/components/Actor/utils/StatePriority.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Actor/Common/AudioSource.hpp>
#include <abyss/views/Actor/Common/EnemyDeadEffect.hpp>

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
		m_pActor->getModule<Flush>()->start(0, 0.5);

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
		co_await BehaviorUtil::WaitForSeconds(m_pActor, 1.0);
		// 爆発
		{
			auto region = m_pActor->find<Body>()->region();

			for (int32 count : step(20)) {
				if (count == 4 || count == 5 || count == 11 || count == 12) {
					// 画面フラッシュ
					m_pActor->getModule<Flush>()->start(0.1);
				}
				auto effectPos = s3d::RandomVec2(region);
				m_pActor->getModule<Effects>()->createWorldFront<EnemyDeadEffect>(effectPos);
				m_pActor->find<AudioSource>()->playAt(U"Damage", effectPos);

				co_await BehaviorUtil::WaitForSeconds(m_pActor, 0.2);
			}
		}
		m_pActor->destroy();
		co_return;
	}
	void DeadState::update()
	{
	}
}
