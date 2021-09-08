#pragma once
#include"BaseState.hpp"

namespace abyss::Actor::Player
{
    class DeadState final : public BaseState
    {
        void start()override;
        void update()override;
    public:
        DeadState();
    private:
        TimerEx m_deadTimer;
    };
}