#pragma once

#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Coro/Fiber/Fiber.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
    class Behavior
    {
    public:
        static Coro::Fiber<> Stab(ActorObj* pActor);
        static Coro::Fiber<> PursuitStab(ActorObj* pActor);
    };
}