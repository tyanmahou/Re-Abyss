#pragma once
#include "CaptainTakoBaseState.hpp"

namespace abyss
{
    class CaptainTakoAttackState : public CaptainTakoBaseState
    {
        TimerEx m_intervalTimer;
        s3d::int32 m_currentAttackCount = 0;
        s3d::int32 m_attackCount = 3;
    public:
        CaptainTakoAttackState();
        void update(double dt) override;
        void draw()const override;
    };
}