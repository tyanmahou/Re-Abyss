#pragma once
#include <abyss/components/Actor/Enemy/KingDux/State/BaseState.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    class AppearState final :
        public BaseState
    {
    public:
        void start() override;
        void end() override;
        Coro::Task<> task() override;
        void update() override;
    private:
    };
}