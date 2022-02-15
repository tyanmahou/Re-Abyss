#include <abyss/components/Actor/Enemy/KingDux/Behavior.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/AppearState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/WaitState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/StabState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/PursuitStabState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/DanceState.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/params/Actor/Enemy/KingDux/Param.hpp>

#include <abyss/utils/Coro/Wait/Wait.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    Coro::Task<> BehaviorSequence::Root(ActorObj* pActor)
    {
        // 前半パターン
        pActor->find<BehaviorCtrl>()->setBehavior(Behavior::Petern);
        // HP 1/2まで
        co_await Coro::WaitUntil([pActor] {
            return pActor->find<HP>()->isUnderPercent(1.0 / 2.0);
        });
        // 後半パターン
        pActor->find<BehaviorCtrl>()->setBehavior(Behavior::Petern2);
    }
    Coro::Task<> Behavior::Petern(ActorObj* pActor)
    {
        co_await Appear(pActor);

        co_await BehaviorUtil::WaitForSeconds(pActor, 0.5);

        while (true) {
            // 突き
            co_await Stab(pActor);

            co_await Stab2(pActor);

            co_await Stab3(pActor);
        }
        co_return;
    }
    Coro::Task<> Behavior::Petern2(ActorObj* pActor)
    {
        while (true)
        {
            co_await Convene(pActor);
            co_await BehaviorUtil::WaitForSeconds(pActor, 0.5);
            co_await PursuitStab(pActor);

            co_await Stab(pActor);

            co_await Convene(pActor);
            co_await BehaviorUtil::WaitForSeconds(pActor, 0.5);
            co_await PursuitStab(pActor);

            co_await Stab2(pActor);

            co_await Convene(pActor);
            co_await BehaviorUtil::WaitForSeconds(pActor, 0.5);
            co_await PursuitStab(pActor);

            co_await Stab3(pActor);
        }
    }
    Coro::Task<> Behavior::Appear(ActorObj* pActor)
    {
        pActor->find<StateCtrl>()->changeState<AppearState>();
        co_yield{};
    }
    Coro::Task<> Behavior::Wait(ActorObj* pActor)
    {
        pActor->find<StateCtrl>()->changeState<WaitState>();
        co_yield{};
    }
    Coro::Task<> Behavior::Stab(ActorObj* pActor)
    {
        pActor->find<StateCtrl>()->changeState<StabState>(TentacleParam::Stab::Tentacle);
        co_yield{};
    }
    Coro::Task<> Behavior::Stab2(ActorObj* pActor)
    {
        pActor->find<StateCtrl>()->changeState<StabState>(TentacleParam::Stab::Tentacle2);
        co_yield{};
    }
    Coro::Task<> Behavior::Stab3(ActorObj* pActor)
    {
        pActor->find<StateCtrl>()->changeState<StabState>(TentacleParam::Stab::Tentacle3);
        co_yield{};
    }
    Coro::Task<> Behavior::PursuitStab(ActorObj* pActor)
    {
        pActor->find<StateCtrl>()->changeState<PursuitStabState>();
        co_yield{};
    }
    Coro::Task<> Behavior::Convene(ActorObj* pActor)
    {
        pActor->find<StateCtrl>()->changeState<DanceState>();
        co_yield{};
    }
}
