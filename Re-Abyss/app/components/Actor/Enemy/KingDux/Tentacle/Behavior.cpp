#include "Behavior.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/Main.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/State/AppearState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/State/RotateState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/State/StabPrevState.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
    Coro::Task<> Behavior::PursuitStab(ActorObj* pActor)
    {
        pActor->find<StateCtrl>()->changeState<AppearState>();
        co_yield{};

        pActor->find<StateCtrl>()->changeState<RotateState>();
        co_yield{};

        co_await BehaviorUtil::WaitForSeconds(pActor, pActor->find<Main>()->getWaitTimeSec());

        pActor->find<StateCtrl>()->changeState<StabPrevState>();
        co_yield{};
    }
}
