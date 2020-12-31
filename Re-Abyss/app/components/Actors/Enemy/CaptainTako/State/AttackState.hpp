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
        Task<> start() override;
        void update() override;

        void draw() const override;
    };
}