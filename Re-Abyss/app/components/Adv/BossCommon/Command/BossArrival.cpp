#include <abyss/components/Adv/BossCommon/Command/BossArrival.hpp>
#include "BossArrival.hpp"

namespace abyss::Adv::BossCommon
{
    BossArrival::BossArrival(AdvObj* pObj):
        m_pObj(pObj)
    {
    }
    void BossArrival::onStart()
    {
    }
    void BossArrival::onEnd()
    {
    }
    Coro::Fiber<> BossArrival::onCommand()
    {
        co_return;
    }
}
