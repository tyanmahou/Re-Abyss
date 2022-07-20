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
        [[nodiscard]] static Coro::Task<> Phase1(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Phase2(ActorObj* pActor);
    public:
        [[nodiscard]] static Coro::Task<> TryToAppear(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Appear(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Angry(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Dead(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Wait(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Stab(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Stab2(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Stab3(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> StabBy(ActorObj* pActor, int id);
        [[nodiscard]] static Coro::Task<> PursuitStab(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Convene(ActorObj* pActor);

        [[nodiscard]] static Coro::Task<> ConveneWhenNotExistBaby(ActorObj* pActor);
    };
}
