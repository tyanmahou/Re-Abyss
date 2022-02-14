#pragma once
#include <abyss/components/Actor/Enemy/KingDux/BabyDux/State/BaseState.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
    class MoveState final :
        public BaseState
    {
    public:
        void start() override;
        Task<> task() override;

        void update() override;
    private:
        void jump();
    private:
        s3d::Vec2 m_startPos;
    };
}