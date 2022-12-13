#pragma once
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/State/BaseState.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
    class StabState final :
        public BaseState
    {
    public:
        void start() override;
        void end() override;
        Coro::Fiber<> task() override;
    };
}