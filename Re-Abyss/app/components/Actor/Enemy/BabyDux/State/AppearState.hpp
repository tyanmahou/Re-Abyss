#pragma once
#include <abyss/components/Actor/Enemy/BabyDux/State/BaseState.hpp>

namespace abyss::Actor::Enemy::BabyDux
{
    class AppearState final :
        public BaseState
    {
    public:
        void start() override;
        Fiber<> task() override;
    private:
    };
}
