#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/components/Actor/Common/HP.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
#include <abyss/utils/Coro/Fiber/FiberUtil.hpp>

namespace abyss::Actor
{
	Coro::Fiber<> BehaviorUtil::WaitForSeconds(ActorObj* pActor, double sec)
	{
		return WaitForSeconds(pActor, s3d::Duration(sec));
	}

	Coro::Fiber<> BehaviorUtil::WaitForSeconds(ActorObj* pActor, s3d::Duration duration)
	{
		TimeLite::Timer timer(duration.count());
		while (true) {
			timer.update(pActor->deltaTime());
			if (timer.isEnd()) {
				break;
			}
			co_yield{};
		}
	}

	Coro::Fiber<> BehaviorUtil::Freeze()
	{
		while (true) {
			co_yield{};
		}
	}

	Coro::Fiber<> BehaviorUtil::WaitLessThanHpRate(ActorObj* pActor, double rate)
	{
		auto hp = pActor->find<HP>();
		if (!hp) {
			co_return;
		}
		co_await Coro::FiberUtil::WaitUntil([hp, rate] {
			return hp->isLessThanRate(rate);
		});
	}

	Coro::Fiber<> BehaviorUtil::GlobalSlowmotion(ActorObj* pActor, s3d::Duration duration, std::function<double(double)> easing)
	{
        auto globalTimeScale = std::make_shared<GlobalTimeScale>();
        pActor->getModule<GlobalTime>()->addTimeScale(globalTimeScale);
        Timer timer(duration, StartImmediately::Yes);
        while (!timer.reachedZero()) {
            globalTimeScale->setScale(easing(timer.progress0_1()));
            co_yield{};
        }
	}

}
