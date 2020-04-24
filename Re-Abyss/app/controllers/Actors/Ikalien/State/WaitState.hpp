#pragma once
#include "BaseState.hpp"

namespace abyss::Ikalien
{
    class WaitState : public BaseState
    {
    public:
        void update(double dt) override;
        void draw()const override;
    };
}