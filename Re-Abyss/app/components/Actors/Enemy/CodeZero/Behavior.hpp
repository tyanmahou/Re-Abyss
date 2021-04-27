#pragma once

#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class Behavior
    {
    public:
        static Coro::Task<> Petern1(ActorObj* pActor);
        static Coro::Task<> Petern2(ActorObj* pActor);
        static Coro::Task<> Petern3(ActorObj* pActor);
    };
}