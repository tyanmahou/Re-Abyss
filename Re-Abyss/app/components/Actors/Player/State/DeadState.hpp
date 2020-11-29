#pragma once
#include"BaseState.hpp"

namespace abyss::Actor::Player
{
    class DeadState final : public BaseState
    {
        TimerEx m_deadTimer;
        void onMove(double dt) override;
        void start()override;
        void update()override;
        void onDraw(const PlayerVM& view)const override;
        void onCollisionStay(IActor* col) override;
    public:
        DeadState();

    };
}