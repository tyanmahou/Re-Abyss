#pragma once
#include <abyss/components/Actor/Enemy/KingDux/State/BaseState.hpp>
#include <abyss/params/Actor/Enemy/KingDux/TentacleParam.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    class StabState final:
        public BaseState
    {
    public:
        StabState(const s3d::Array<TentacleDesc>& desc = TentacleParam::Stab::Tentacle);

        void start() override;
        void end() override;
        Fiber<void> task() override;
    private:
        const s3d::Array<TentacleDesc>& m_tentacleDesc;
        s3d::Array<Ref<ActorObj>> m_tentacles;
    };
}