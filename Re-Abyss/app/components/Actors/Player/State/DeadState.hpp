#pragma once
#include"BaseState.hpp"

namespace abyss::Actor::Player
{
    class DeadState final : public BaseState
    {
        TimerEx m_deadTimer;
        Task<> start()override;
        void update()override;
        void onDraw(const PlayerVM& view)const override;
        void onPostCollision() override;
    public:
        DeadState();

    };
}