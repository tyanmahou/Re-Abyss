#pragma once
#include"BaseState.hpp"

namespace abyss::Actor::Player
{
    class LadderState final : public BaseState
    {
        double m_ladderTopTimer = 0;
        bool m_isTop = false;
    private:
        void onMove(double dt) override;
        void onLanding() override;

        bool onCollisionStayLadderTop(const LadderProxy& ladder) override;

        void start()override;
        void update()override;
        void lastUpdate()override;
        void onDraw(const PlayerVM& view)const override;

        bool isLadderTop()const;
    };
}