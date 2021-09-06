#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::CaptainTako
{
    class AttackState : public BaseState
    {
        s3d::int32 m_currentAttackCount = 0;
        s3d::int32 m_attackCount = 3;
    public:
        AttackState();
        void start() override;
        Task<> task() override;
        void update() override;
    };
}