#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::LaunShark::Shot
{
    class PursuitState final : public BaseState
    {
        TimerEx m_timer;
    public:
        PursuitState();

        Task<> start() override;
        void update() override;

        void draw()const override;
    };
}