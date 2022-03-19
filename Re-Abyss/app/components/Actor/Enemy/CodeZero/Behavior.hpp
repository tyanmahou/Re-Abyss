#pragma once
#include <abyss/components/Actor/Common/BehaviorCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/HandProxy.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class BehaviorSequence
    {
    public:
        [[nodiscard]] static Coro::Task<> Root(BehaviorCtrl* behavior);
    };
    class Behavior
    {
    public:
        static Coro::Task<> Phase1(ActorObj* pActor);
        static Coro::Task<> Phase2(ActorObj* pActor);
        static Coro::Task<> Phase3(ActorObj* pActor);
    public:
        static Coro::Task<> Dead(ActorObj* pActor);
        static Coro::Task<> LeftAttack(ActorObj* pActor);
        static Coro::Task<> RightAttack(ActorObj* pActor);
        static Coro::Task<> BothAttack(ActorObj* pActor);

        static Coro::Task<> LeftAttackAndWait(ActorObj* pActor, double waitSec);
        static Coro::Task<> RightAttackAndWait(ActorObj* pActor, double waitSec);
        static Coro::Task<> BothAttackAndWait(ActorObj* pActor, double waitSec);

        static Coro::Task<> RollingAttack(ActorObj* pActor, bool isReverse);
        static Coro::Task<> ChargeShot(ActorObj* pActor);

        static Coro::Task<> ChangeHandsPhase1(ActorObj* pActor, bool slowStart = false);
        static Coro::Task<> ChangeHandsPhase2(ActorObj* pActor, bool slowStart = false);

        static Coro::Task<> WaitPursuitHands(ActorObj* pActor);
    };
}