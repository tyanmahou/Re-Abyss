#pragma once
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/State/BaseState.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
    class ReturnState final :
        public BaseState
    {
    public:
        void start() override;
        Coro::Task<> task() override;
    };
}