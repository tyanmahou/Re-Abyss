#pragma once
#include <abyss/components/Actor/Enemy/KingDux/State/BaseState.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    class StabState final:
        public BaseState
    {
    public:
        void start() override;
        Task<void> task() override;
    private:
        Task<void> subTask();
        Task<void> subTask2();
    private:
        s3d::Array<Ref<ActorObj>> m_tentacles;
    };
}