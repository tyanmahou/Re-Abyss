#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::Ikalien
{
    class WaitState : public BaseState
    {
    public:
        Task<> start()override;
        void update() override;
        void draw() const override;
    };
}