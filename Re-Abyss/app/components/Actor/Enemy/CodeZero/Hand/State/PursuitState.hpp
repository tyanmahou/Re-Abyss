#pragma once
#include "BaseState.hpp"
#include <abyss/utils/TimerEx/TimerEx.hpp>
namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class PursuitState final : public BaseState
    { 
    public:
        void update() override;
        void start()override;
        void lastUpdate() override;
    };
}