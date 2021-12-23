#include "BehaviorUtil.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

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

}
