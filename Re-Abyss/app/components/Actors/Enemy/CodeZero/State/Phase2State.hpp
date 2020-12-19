#pragma once
#include "BaseState.hpp"
namespace abyss::Actor::Enemy::CodeZero
{
    class Phase2State : public BaseState
    {
    public:
        Phase2State();
        Task<> start() override;
        void update() override;
    };
}