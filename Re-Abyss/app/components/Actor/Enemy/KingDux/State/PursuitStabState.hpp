#pragma once
#include <abyss/components/Actor/Enemy/KingDux/State/BaseState.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    class PursuitStabState final :
        public BaseState
    {
    public:
        void start() override;
        void end() override;
        Fiber<void> task() override;
    private:
        s3d::Array<Ref<ActorObj>> m_tentacles;
    };
}