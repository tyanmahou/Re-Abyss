#include "BehaviorUtil.hpp"
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/utils/Coro/Wait/Wait.hpp>

namespace abyss::Actor::BehaviorUtils
{
    Coro::Task<> WaitForSeconds(IActor* pActor, double sec)
    {
        return WaitForSeconds(pActor, s3d::Duration(sec));
    }

    Coro::Task<> WaitForSeconds(IActor* pActor, s3d::Duration duration)
    {
        co_yield Coro::WaitForSecondsEx(duration, pActor->getUpdateClock());
    }

}
