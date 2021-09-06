#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::Ikalien
{
    class WaitState : public BaseState
    {
    public:
        void start()override;
        void update() override;
    };
}