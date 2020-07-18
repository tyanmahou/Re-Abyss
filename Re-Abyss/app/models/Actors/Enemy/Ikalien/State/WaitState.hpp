#pragma once
#include "BaseState.hpp"

namespace abyss::Ikalien
{
    class WaitState : public BaseState
    {
    public:
        void start()override;
        void update(double dt) override;
    };
}