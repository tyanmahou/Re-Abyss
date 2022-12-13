#pragma once
#include <abyss/components/Actor/Common/BehaviorCtrl.hpp>

namespace abyss::Actor::Enemy::KingDux
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
    public:
        [[nodiscard]] static Coro::Fiber<> TryToAppear(ActorObj* pActor);
        [[nodiscard]] static Coro::Fiber<> Appear(ActorObj* pActor);
        [[nodiscard]] static Coro::Fiber<> Angry(ActorObj* pActor);
        [[nodiscard]] static Coro::Fiber<> Dead(ActorObj* pActor);
        [[nodiscard]] static Coro::Fiber<> Wait(ActorObj* pActor);
        [[nodiscard]] static Coro::Fiber<> Stab(ActorObj* pActor);
        [[nodiscard]] static Coro::Fiber<> Stab2(ActorObj* pActor);
        [[nodiscard]] static Coro::Fiber<> Stab3(ActorObj* pActor);
        [[nodiscard]] static Coro::Fiber<> StabBy(ActorObj* pActor, int id);
        [[nodiscard]] static Coro::Fiber<> PursuitStab(ActorObj* pActor);
        [[nodiscard]] static Coro::Fiber<> Convene(ActorObj* pActor);

        [[nodiscard]] static Coro::Fiber<> ConveneWhenNotExistBaby(ActorObj* pActor);
    };
}
