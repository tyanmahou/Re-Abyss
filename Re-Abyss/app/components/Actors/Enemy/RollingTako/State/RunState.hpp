#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::RollingTako
{
    class RunState : public BaseState
    {
    public:
        Task<> start()override;
        void update() override;

        void draw() const override;
    };
}