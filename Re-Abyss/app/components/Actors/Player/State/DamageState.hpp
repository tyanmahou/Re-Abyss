#pragma once
#include"BaseState.hpp"

namespace abyss::Actor::Player
{
    class DamageState final : public BaseState
    {
        TimerEx m_damageTimer;
        Task<> start()override;
        void update()override;
        void onDraw(const PlayerVM& view)const override;
    public:
        DamageState();

    };
}