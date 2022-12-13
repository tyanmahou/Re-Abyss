#pragma once
#include <abyss/components/Actor/Common/BehaviorCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/HandProxy.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class BehaviorSequence
    {
    public:
        [[nodiscard]] static Coro::AsyncGenerator<BehaviorFunc> Root(ActorObj* pActor);
    };
    class Behavior
    {
    public:
        [[nodiscard]] static Coro::Fiber<> Phase1(ActorObj* pActor);
        [[nodiscard]] static Coro::Fiber<> Phase2(ActorObj* pActor);
        [[nodiscard]] static Coro::Fiber<> Phase3(ActorObj* pActor);
    public:
        [[nodiscard]] static Coro::Fiber<> TryToAppear(ActorObj* pActor);
        [[nodiscard]] static Coro::Fiber<> Appear(ActorObj* pActor);
        [[nodiscard]] static Coro::Fiber<> Angry(ActorObj* pActor);
        [[nodiscard]] static Coro::Fiber<> Dead(ActorObj* pActor);
        [[nodiscard]] static Coro::Fiber<> LeftAttack(ActorObj* pActor);
        [[nodiscard]] static Coro::Fiber<> RightAttack(ActorObj* pActor);
        [[nodiscard]] static Coro::Fiber<> BothAttack(ActorObj* pActor);

        [[nodiscard]] static Coro::Fiber<> LeftAttackAndWait(ActorObj* pActor, double waitSec);
        [[nodiscard]] static Coro::Fiber<> RightAttackAndWait(ActorObj* pActor, double waitSec);
        [[nodiscard]] static Coro::Fiber<> BothAttackAndWait(ActorObj* pActor, double waitSec);

        [[nodiscard]] static Coro::Fiber<> RollingAttack(ActorObj* pActor, bool isReverse);
        [[nodiscard]] static Coro::Fiber<> ChargeShot(ActorObj* pActor);

        [[nodiscard]] static Coro::Fiber<> ChangeHandsPhase1(ActorObj* pActor, bool slowStart = false);
        [[nodiscard]] static Coro::Fiber<> ChangeHandsPhase2(ActorObj* pActor, bool slowStart = false);

        [[nodiscard]] static Coro::Fiber<> WaitPursuitHands(ActorObj* pActor);
    };
}