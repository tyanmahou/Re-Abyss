#pragma once
#include <abyss/components/Actor/Common/BehaviorCtrl.hpp>

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
        static Coro::Task<> Pettern1(ActorObj* pActor);
        static Coro::Task<> Pettern2(ActorObj* pActor);
        static Coro::Task<> Pettern3(ActorObj* pActor);
    public:
        static Coro::Task<> WaitPursuitHands(ActorObj* pActor);
    };
}