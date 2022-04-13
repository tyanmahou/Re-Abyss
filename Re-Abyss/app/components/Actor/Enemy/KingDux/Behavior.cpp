#include <abyss/components/Actor/Enemy/KingDux/Behavior.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/DeadCheacker.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/AppearState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/AngryState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/WaitState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/StabState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/PursuitStabState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/State/DanceState.hpp>
#include <abyss/components/Actor/Enemy/KingDux/BabyCtrl.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/params/Actor/Enemy/KingDux/Param.hpp>

#include <abyss/utils/Coro/Task/Wait.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    Coro::Task<> BehaviorSequence::Root(BehaviorCtrl* behavior)
    {
        auto* pActor = behavior->getActor();

        // 前半パターン
        behavior->setBehavior(Behavior::Phase1);
        // HP 1/2まで
        co_await BehaviorUtil::WaitLessThanHpRate(pActor, 1.0 / 2.0);
        // 後半パターン
        behavior->setBehavior(Behavior::Phase2);
        // 強制遷移
        behavior->setActiveBehavior(true);
    }
    Coro::Task<> Behavior::Phase1(ActorObj* pActor)
    {
        co_await Appear(pActor);

        co_await BehaviorUtil::WaitForSeconds(pActor, 0.5);

        int32 stabId = Random(2);
        while (true) {
            // 突き
            co_await StabBy(pActor, stabId);
            co_await BehaviorUtil::WaitForSeconds(pActor, 1.0);
            stabId = (stabId + 1) % 3;
        }
        co_return;
    }
    Coro::Task<> Behavior::Phase2(ActorObj* pActor)
    {
        co_await Angry(pActor);

        int32 stabId = Random(2);
        while (true)
        {
            co_await ConveneWhenNotExistBaby(pActor);
            co_await BehaviorUtil::WaitForSeconds(pActor, 0.5);
            co_await PursuitStab(pActor);

            co_await StabBy(pActor, stabId);
            stabId = (stabId + 1) % 3;
        }
    }
    Coro::Task<> Behavior::Appear(ActorObj* pActor)
    {
        pActor->find<StateCtrl>()->changeState<AppearState>();
        co_yield{};
    }
    Coro::Task<> Behavior::Angry(ActorObj* pActor)
    {
        pActor->find<StateCtrl>()->changeState<AngryState>();
        co_yield{};
    }
    Coro::Task<> Behavior::Dead(ActorObj* pActor)
    {
        pActor->find<DeadChecker>()->requestDead();
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
    Coro::Task<> Behavior::StabBy(ActorObj* pActor, int id)
    {
        switch (id)
        {
        case 0:
            return Stab(pActor);
        case 1:
            return Stab2(pActor);
        case 2:
            return Stab3(pActor);
        }
        return Stab(pActor);
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
    Coro::Task<> Behavior::ConveneWhenNotExistBaby(ActorObj* pActor)
    {
        if (!pActor->find<BabyCtrl>()->isExistBaby()) {
            co_await Convene(pActor);
        }
        co_return;
    }
}
