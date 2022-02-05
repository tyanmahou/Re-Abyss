#pragma once
#include <abyss/components/Actor/Enemy/KingDux/BabyDux/State/BaseState.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
    class AppearState final :
        public BaseState
    {
    public:
        void start() override;
        Task<> task() override;
    private:
    };
}