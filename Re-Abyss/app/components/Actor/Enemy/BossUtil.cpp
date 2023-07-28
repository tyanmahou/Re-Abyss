#include <abyss/components/Actor/Enemy/BossUtil.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Sfx/SpecialEffects.hpp>

#include <abyss/components/Actor/Common/AudioSource.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/BossFadeMask.hpp>
#include <abyss/components/Actor/Common/ColorAnim/BossDeadColor.hpp>
#include <abyss/components/Actor/Enemy/SeDef.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/components/Effect/Actor/Common/EnemyDead/Builder.hpp>
#include <abyss/components/Effect/Common/BossFadeMask.hpp>
#include <abyss/components/Effect/Common/EmissiveCtrl.hpp>
#include <abyss/utils/Coro/Fiber/MultiFibers.hpp>
#include <abyss/utils/Coro/Fiber/FiberUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy
{
	Coro::Fiber<> BossUtil::DeadDemo(ActorObj* pActor)
	{
		co_await BehaviorUtil::WaitForSeconds(pActor, 1.0);
		// 爆発
		{
			Coro::MultiFibers multiFibers{};
			
			multiFibers.add([pActor]()->Coro::Fiber<>{
				// ボスフェード開始
				auto* bossFade = pActor->getModule<SpecialEffects>()->bossFade();
				bossFade->start();

				auto region = pActor->find<Body>()->region();

				const auto flushCounts = Array{ 4, 5, 11, 12, 18, 19, 25, 26 };
				size_t flushCountIndex = 0;
				const size_t flushCountsSize = flushCounts.size();

				for (int32 count : step(45)) {
					if (flushCountIndex < flushCountsSize && count == flushCounts[flushCountIndex]) {
						++flushCountIndex;
						// 画面フラッシュ
						pActor->getModule<SpecialEffects>()->flush()->start(0.1);
					}
					auto effectPos = s3d::RandomVec2(region);
					RequestDeadEffect(pActor, effectPos);

					pActor->find<AudioSource>()->playAt(SeDef::Damage, effectPos);

					co_await BehaviorUtil::WaitForSeconds(pActor, 0.2);
				}
				co_await Coro::FiberUtil::WaitUntil([&] {
					return bossFade->isFadeOutEnd();
				});
			});
			multiFibers.add([pActor]()->Coro::Fiber<> {
				co_await BehaviorUtil::WaitForSeconds(pActor, 2.0s);

				// 死亡カラーアニメ
				pActor->find<ColorAnim::BossDeadColor>()->startAnim(4.0);
			});
			co_await multiFibers.whenAll();
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
