#pragma once
#include"BaseState.hpp"

namespace abyss::Player
{
    class DeadState final : public BaseState
    {
        TimerEx m_deadTimer;
        void onMove(double dt) override;
        void start()override;
        void update(double dt)override;
        void onDraw(const PlayerVM& view)const override;
        void onCollisionStay(IActor* col) override;
    public:
        DeadState();

    };
}