#pragma once
#include "BaseState.hpp"

namespace abyss::RollingTako
{
    class WaitState : public BaseState
    {
    public:
        void start()override;
        void update(double dt) override;

        void draw() const override;
    };
}