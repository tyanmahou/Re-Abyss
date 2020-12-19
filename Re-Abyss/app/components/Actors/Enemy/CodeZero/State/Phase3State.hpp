#pragma once
#include "BaseState.hpp"
namespace abyss::Actor::Enemy::CodeZero
{
    class Phase3State : public BaseState
    {
    public:
        Phase3State();
        Task<> start() override;
        void update() override;
    };
}