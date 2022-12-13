#pragma once
#include <abyss/components/Actor/Enemy/BazookaKun/State/BaseState.hpp>

namespace abyss::Actor::Enemy::BazookaKun
{
    class WaitState final :
        public BaseState
    {
    public:
        void start() override;
        void update() override;
        Fiber<> task() override;
    private:
    };
}
