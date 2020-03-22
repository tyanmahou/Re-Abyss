#pragma once
#include"PlayerBaseState.hpp"

namespace abyss
{
    class PlayerLadderState final : public PlayerBaseState
    {
        double m_ladderTopTimer = 0;
        bool m_isTop = false;
        bool m_canLadder = true;
    private:
        void onMove(double dt) override;
        void onLanding() override;

        void onCollisionStay(const LadderActor& col) override;

        void start()override;
        void update(double dt)override;
        void onDraw(const PlayerVM& view)const override;

        bool isLadderTop()const;
    };
}