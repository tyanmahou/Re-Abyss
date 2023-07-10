#pragma once
#include <abyss/components/Actor/Enemy/BabyDux/State/BaseState.hpp>

namespace abyss::Actor::Enemy::BabyDux
{
    class MoveState final :
        public BaseState
    {
    public:
        void start() override;
        Fiber<> updateAsync() override;

        void update() override;
    private:
        Fiber<> taskCharge();
        Fiber<> taskJump();
    private:
        s3d::Vec2 m_startPos;
    };
}
