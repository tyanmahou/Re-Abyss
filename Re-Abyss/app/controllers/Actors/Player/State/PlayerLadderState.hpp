#pragma once
#include"PlayerBaseState.hpp"

namespace abyss
{
    class PlayerLadderState final : public PlayerBaseState
    {
        double m_ladderTopTimer = 0;
        bool m_isTop = false;
    private:
        void onMove(double dt) override;
        void onLanding() override;

        void onCollisionStayLadderTop(const LadderActor& ladder) override;

        void start()override;
        void update(double dt)override;
        void lastUpdate(double dt)override;
        void onDraw(const PlayerVM& view)const override;

        bool isLadderTop()const;
    };
}