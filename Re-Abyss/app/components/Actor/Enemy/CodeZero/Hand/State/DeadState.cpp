#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/DeadState.hpp>

#include <abyss/components/Actor/utils/StatePriority.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/components/Actor/Common/ShakeCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/KindCtrl.hpp>
#include <abyss/utils/Coro/Fiber/FiberUtil.hpp>
#include <abyss/modules/Sfx/SpecialEffects.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
	void DeadState::Change(ActorObj* pActor)
	{
		pActor->find<StateCtrl>()->changeState<DeadState, StatePriority::Dead>();
	}
	void DeadState::start()
	{
		// 当たりむこう
		m_colCtrl->setActive(false);

        // 動作停止
        m_handMove->stop();
	}
	void DeadState::end()
	{
	}
	Coro::Fiber<> DeadState::updateAsync()
	{
        // フェード開始を待つ
        auto* bossFade = m_pActor->getModule<SpecialEffects>()->bossFade();
        co_await Coro::FiberUtil::WaitUntil([bossFade] {return bossFade->isActive(); });

        // 左右でタイミングをずらす
        bool isLeft = m_pActor->find<KindCtrl>()->isLeftHand();
        co_await BehaviorUtil::WaitForSeconds(m_pActor, isLeft ? 3.0: 4.5);
        // 揺れる
        m_pActor->find<ShakeCtrl>()->request(5.0, 0.4);
        co_await BehaviorUtil::WaitForSeconds(m_pActor, 0.65);

        //　落下
        m_pActor->find<ShakeCtrl>()->request(2.0, -1);
        m_handMove->setActive(true);
        m_handMove->startDeadFall();

		co_return;
	}
	void DeadState::update()
	{
	}
}
