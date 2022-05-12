#include <abyss/components/Actor/Enemy/BossUtil.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Sfx/SpecialEffects.hpp>

#include <abyss/components/Actor/Common/AudioSource.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/components/Effect/Actor/Common/EnemyDead/Builder.hpp>
#include <abyss/components/Effect/Common/BossFadeMask.hpp>
#include <abyss/components/Effect/Common/EmissiveCtrl.hpp>
#include <abyss/utils/Coro/Task/Wait.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::Enemy
{
	Coro::Task<> BossUtil::DeadDemo(ActorObj* pActor)
	{
		co_await BehaviorUtil::WaitForSeconds(pActor, 1.0);
		// 爆発
		{
			// ボスフェード開始
			auto* bossFade = pActor->getModule<SpecialEffects>()->bossFade();
			bossFade->start();

			auto region = pActor->find<Body>()->region();

			for (int32 count : step(45)) {
				if (count == 4 || count == 5 || count == 11 || count == 12
					|| count == 18 || count == 19 || count == 25 || count == 26
					) {
					// 画面フラッシュ
					pActor->getModule<SpecialEffects>()->flush()->start(0.1);
				}
				auto effectPos = s3d::RandomVec2(region);
				RequestDeadEffect(pActor, effectPos);

				pActor->find<AudioSource>()->playAt(U"Damage", effectPos);

				co_await BehaviorUtil::WaitForSeconds(pActor, 0.2);
			}
			co_await Coro::WaitUntil([&] {
				return bossFade->isFadeOutEnd();
			});
		}
		pActor->destroy();
	}
	Ref<Effect::EffectObj> BossUtil::RequestDeadEffect(ActorObj* pActor, const s3d::Vec2& pos)
	{
		auto effectObj = pActor->getModule<Effects>()->createWorldFront<Effect::Actor::EnemyDead::Builder>(pos);
		effectObj->attach<Effect::BossFadeMask>(effectObj.get());
		effectObj->attach<Effect::EmissiveCtrl>(effectObj.get());
		return effectObj;
	}
}
