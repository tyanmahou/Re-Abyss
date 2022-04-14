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
        [[nodiscard]] static Coro::Task<> Phase1(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Phase2(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Phase3(ActorObj* pActor);
    public:
        [[nodiscard]] static Coro::Task<> Appear(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Angry(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Dead(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> LeftAttack(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> RightAttack(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> BothAttack(ActorObj* pActor);

        [[nodiscard]] static Coro::Task<> LeftAttackAndWait(ActorObj* pActor, double waitSec);
        [[nodiscard]] static Coro::Task<> RightAttackAndWait(ActorObj* pActor, double waitSec);
        [[nodiscard]] static Coro::Task<> BothAttackAndWait(ActorObj* pActor, double waitSec);

        [[nodiscard]] static Coro::Task<> RollingAttack(ActorObj* pActor, bool isReverse);
        [[nodiscard]] static Coro::Task<> ChargeShot(ActorObj* pActor);

        [[nodiscard]] static Coro::Task<> ChangeHandsPhase1(ActorObj* pActor, bool slowStart = false);
        [[nodiscard]] static Coro::Task<> ChangeHandsPhase2(ActorObj* pActor, bool slowStart = false);

        [[nodiscard]] static Coro::Task<> WaitPursuitHands(ActorObj* pActor);
    };
}