#pragma once
#include"BaseState.hpp"

namespace abyss::Player
{
    class DamageState final : public BaseState
    {
        TimerEx m_damageTimer;
        void onMove(double dt) override;
        void start()override;
        void update(double dt)override;
        void onDraw(const PlayerVM& view)const override;
    public:
        DamageState();

    };
}