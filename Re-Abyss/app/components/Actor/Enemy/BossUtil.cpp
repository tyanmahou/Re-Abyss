#include <abyss/components/Actor/Enemy/BossUtil.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Sfx/SpecialEffects.hpp>

#include <abyss/components/Actor/Common/AudioSource.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/BossFadeMask.hpp>
#include <abyss/components/Actor/Common/ColorAnim/BossDeadColor.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/components/Effect/Actor/Common/EnemyDead/Builder.hpp>
#include <abyss/components/Effect/Common/BossFadeMask.hpp>
#include <abyss/components/Effect/Common/EmissiveCtrl.hpp>
#include <abyss/utils/Coro/Task/Wait.hpp>

#include <Siv3D.hpp>

namespace
{
	using namespace abyss;

	class MultiTask
	{
	public:
		MultiTask() = default;

		MultiTask& add(const std::function<Coro::Task<>()>& task)
		{
			m_tasks.push_back(task);
			return *this;
		}

		Coro::Task<> operator()()
		{
			s3d::Array<Coro::Task<>> tasks;
			for (auto&& task : m_tasks) {
				tasks.push_back(task());
			}
			while (true) {
				for (auto&& task : tasks) {
					task.moveNext();
				}
				if (tasks.all([](const Coro::Task<>& task) {return task.isDone(); })) {
					break;
				}
				co_yield{};
			}
			co_return;
		}
	private:
		s3d::Array<std::function<Coro::Task<>()>> m_tasks;
	};
}
namespace abyss::Actor::Enemy
{
	Coro::Task<> BossUtil::DeadDemo(ActorObj* pActor)
	{
		co_await BehaviorUtil::WaitForSeconds(pActor, 1.0);
		// 爆発
		{
			MultiTask multiTask{};
			
			multiTask.add([pActor]()->Coro::Task<>{
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

					pActor->find<AudioSource>()->playAt(U"Damage", effectPos);

					co_await BehaviorUtil::WaitForSeconds(pActor, 0.2);
				}
				co_await Coro::WaitUntil([&] {
					return bossFade->isFadeOutEnd();
				});
			});
			multiTask.add([pActor]()->Coro::Task<> {
				// 死亡カラーアニメ
				pActor->find<ColorAnim::BossDeadColor>()->startAnim();

				auto bossFadeMask = pActor->find<BossFadeMask>();

				TimeLite::Timer timer{ 6.0 };
				while (!timer.isEnd()) {
					timer.update(pActor->deltaTime());
					bossFadeMask->setRate(timer.rate());
					co_yield{};
				}
			});

			co_await multiTask();
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
