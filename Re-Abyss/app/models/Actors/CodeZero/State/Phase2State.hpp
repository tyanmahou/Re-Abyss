#pragma once
#include "BaseState.hpp"
namespace abyss::CodeZero
{
    class Phase2State : public BaseState
    {
    public:
        Phase2State();
        void start() override;
        void update(double dt) override;
    };
}