#pragma once
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/State/BaseState.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
    class ReturnState final :
        public BaseState
    {
    public:
        static void Change(ActorObj* pActor);
    public:
        void start() override;
        Coro::Task<> task() override;
    };
}