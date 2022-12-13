#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/HP.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
#include <abyss/utils/Coro/Fiber/Wait.hpp>

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
		co_await Coro::WaitUntil([hp, rate] {
			return hp->isLessThanRate(rate);
		});
	}

}
