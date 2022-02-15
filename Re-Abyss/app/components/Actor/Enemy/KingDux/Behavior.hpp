#pragma once

#include <functional>
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>
#include <abyss/utils/Coro/Generator/Generator.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    class BehaviorSequence
    {
    public:
        [[nodiscard]] static Coro::Task<> Root(ActorObj* pActor);
    };
    class Behavior
    {
    public:
        [[nodiscard]] static Coro::Task<> Petern(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Petern2(ActorObj* pActor);

        [[nodiscard]] static Coro::Task<> Appear(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Wait(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Stab(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Stab2(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Stab3(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> PursuitStab(ActorObj* pActor);
        [[nodiscard]] static Coro::Task<> Convene(ActorObj* pActor);
    };
}