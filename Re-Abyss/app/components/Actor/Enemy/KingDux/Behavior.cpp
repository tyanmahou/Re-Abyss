#include "Behavior.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/AppearState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/StabState.hpp>
#include <Siv3D.hpp>


namespace abyss::Actor::Enemy::KingDux
{
    Coro::Task<> Behavior::Petern(ActorObj* pActor)
    {
        pActor->find<StateCtrl>()->changeState<AppearState>();
        co_yield{};

        while (true) {
            // 突き
            pActor->find<StateCtrl>()->changeState<StabState>();
            co_yield{};
        }
        co_return;
    }
}
