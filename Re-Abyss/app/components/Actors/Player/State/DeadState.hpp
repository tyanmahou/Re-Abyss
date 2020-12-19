#pragma once
#include"BaseState.hpp"

namespace abyss::Actor::Player
{
    class DeadState final : public BaseState
    {
        TimerEx m_deadTimer;
        void onMove(double dt) override;
        Task<> start()override;
        void update()override;
        void onDraw(const PlayerVM& view)const override;
        void onCollisionReact() override;
    public:
        DeadState();

    };
}