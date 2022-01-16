#pragma once
#include <abyss/components/Actor/Enemy/KingDux/State/BaseState.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    class DanceState final :
        public BaseState
    {
    public:
        void start() override;
        Coro::Task<> task() override;
        void update() override;
    private:
    };
}