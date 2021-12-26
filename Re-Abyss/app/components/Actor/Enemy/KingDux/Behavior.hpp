#pragma once

#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    class Behavior
    {
    public:
        static Coro::Task<> Petern(ActorObj* pActor);
        static Coro::Task<> Stab(ActorObj* pActor);
        static Coro::Task<> PursuitStab(ActorObj* pActor);
        static Coro::Task<> Convene(ActorObj* pActor);
    };
}