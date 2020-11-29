#pragma once
#include"BaseState.hpp"

namespace abyss::Actor::Player
{
    class DamageState final : public BaseState
    {
        TimerEx m_damageTimer;
        void onMove(double dt) override;
        void start()override;
        void update()override;
        void onDraw(const PlayerVM& view)const override;
    public:
        DamageState();

    };
}