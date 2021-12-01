#pragma once
#include <abyss/components/Actor/Enemy/KingDux/State/BaseState.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    class WaitState final:
        public BaseState
    {
    public:
        void start() override;
    };
}