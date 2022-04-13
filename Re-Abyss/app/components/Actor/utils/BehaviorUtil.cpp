#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/HP.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
#include <abyss/utils/Coro/Task/Wait.hpp>

namespace abyss::Actor
{
	Coro::Task<> BehaviorUtil::WaitForSeconds(ActorObj* pActor, double sec)
	{
		return WaitForSeconds(pActor, s3d::Duration(sec));
	}

	Coro::Task<> BehaviorUtil::WaitForSeconds(ActorObj* pActor, s3d::Duration duration)
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

	Coro::Task<> BehaviorUtil::Freeze()
	{
		while (true) {
			co_yield{};
		}
	}

	Coro::Task<> BehaviorUtil::WaitLessThanHpRate(ActorObj* pActor, double rate)
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
