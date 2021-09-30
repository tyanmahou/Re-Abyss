#include "BehaviorUtil.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::BehaviorUtils
{
    Coro::Task<> WaitForSeconds(ActorObj* pActor, double sec)
    {
        return WaitForSeconds(pActor, s3d::Duration(sec));
    }

    Coro::Task<> WaitForSeconds(ActorObj* pActor, s3d::Duration duration)
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

}
