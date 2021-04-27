#include "BehaviorUtil.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/utils/Coro/Wait/Wait.hpp>

namespace abyss::Actor::BehaviorUtils
{
    Coro::Task<> WaitForSeconds(ActorObj* pActor, double sec)
    {
        return WaitForSeconds(pActor, s3d::Duration(sec));
    }

    Coro::Task<> WaitForSeconds(ActorObj* pActor, s3d::Duration duration)
    {
        co_yield Coro::WaitForSecondsEx(duration, pActor->getUpdateClock());
    }

}
