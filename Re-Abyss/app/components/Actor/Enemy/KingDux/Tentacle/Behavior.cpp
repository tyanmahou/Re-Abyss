#include "Behavior.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/State/AppearState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/State/RotateState.hpp>
#include <abyss/utils/Coro/Wait/Wait.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
    Coro::Task<> Behavior::PursuitStab(ActorObj* pActor)
    {
        pActor->find<StateCtrl>()->changeState<AppearState>();
        co_yield{};

        pActor->find<StateCtrl>()->changeState<RotateState>();
        co_yield{};
    }
}
