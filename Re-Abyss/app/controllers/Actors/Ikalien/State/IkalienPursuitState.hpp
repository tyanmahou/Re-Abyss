#pragma once
#include "IkalienBaseState.hpp"

namespace abyss
{
    class IkalienPursuitState : public IkalienBaseState
    {
        TimerEx m_timer;
    public:
        IkalienPursuitState();
        void start()override;
        void update(double dt) override;
        void draw()const override;
    };
}