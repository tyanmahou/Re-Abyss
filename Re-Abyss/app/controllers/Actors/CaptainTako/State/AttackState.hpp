#pragma once
#include "BaseState.hpp"

namespace abyss::CaptainTako
{
    class AttackState : public BaseState
    {
        TimerEx m_intervalTimer;
        s3d::int32 m_currentAttackCount = 0;
        s3d::int32 m_attackCount = 3;
    public:
        AttackState();
        void update(double dt) override;
        void draw()const override;
    };
}