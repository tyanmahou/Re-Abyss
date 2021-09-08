#pragma once
#include"BaseState.hpp"

namespace abyss::Actor::Player
{
    class LadderState final : public BaseState
    {
        double m_ladderTopTimer = 0;
        bool m_isTop = false;
    private:
        void onLanding() override;

        void start()override;
        void update()override;
        void lastUpdate()override;

        bool isLadderTop()const;
    };
}