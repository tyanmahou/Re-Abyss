#pragma once
#include"PlayerBaseState.hpp"

namespace abyss
{
    class PlayerDamageState final : public PlayerBaseState
    {
        TimerEx m_damageTimer;
        void onMove(double dt) override;
        void start()override;
        void update(double dt)override;
        void onDraw(const PlayerVM& view)const override;
    public:
        PlayerDamageState();

    };
}