#pragma once
#include <abyss/components/Actor/Common/BehaviorCtrl.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    class BehaviorSequence
    {
    public:
        [[nodiscard]] static Coro::Task<> Root(BehaviorCtrl* behavior);
    };
    class Behavior
    {
    public:
        [[nodiscard]] static Coro::Task<> Pettern1(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Pettern2(ActorObj* pActor);
    public:
        [[nodiscard]] static Coro::Task<> Appear(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Wait(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Stab(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Stab2(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Stab3(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> PursuitStab(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Convene(ActorObj* pActor);
    };
}