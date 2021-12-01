#pragma once
#include <abyss/components/Actor/Enemy/KingDux/State/BaseState.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    class StabState final:
        public BaseState
    {
    public:
        void start() override;
        Task<void> task() override;
    };
}