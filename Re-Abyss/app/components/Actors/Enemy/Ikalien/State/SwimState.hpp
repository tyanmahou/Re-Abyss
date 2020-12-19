#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::Ikalien
{
    class SwimState : public BaseState
    {
    public:
        Task<> start()override;
        void update() override;
        void draw()const override;
    };
}