#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::Ikalien
{
    class SwimState : public BaseState
    {
    public:
        void start()override;
        void update() override;
    };
}