#pragma once

#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class Behavior
    {
    public:
        static Coro::Task Petern1(IActor* pActor);
        static Coro::Task Petern2(IActor* pActor);
        static Coro::Task Petern3(IActor* pActor);
    };
}