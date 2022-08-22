#include <abyss/components/Actor/Enemy/BazookaKun/State/WaitState.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/components/Actor/Enemy/BazookaKun/State/AimState.hpp>
#include <abyss/params/Actor/Enemy/BazookaKun/Param.hpp>

namespace abyss::Actor::Enemy::BazookaKun
{
    void WaitState::start()
    {
    }
    void WaitState::update()
    {
        // ある程度近く前方なら遷移
        if (m_target->isInAimRangeWithDist()) {
            this->changeState<AimState>();
        }
    }
    Task<> WaitState::task()
    {
        co_return;
    }
}
