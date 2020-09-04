#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Ikalien
{
    class WaitState : public BaseState
    {
    public:
        void start()override;
        void update(double dt) override;
        void draw() const override;
    };
}