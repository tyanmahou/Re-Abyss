#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::RollingTako
{
    class RunState : public BaseState
    {
    public:
        void start()override;
        void update(double dt) override;

        void draw() const override;
    };
}