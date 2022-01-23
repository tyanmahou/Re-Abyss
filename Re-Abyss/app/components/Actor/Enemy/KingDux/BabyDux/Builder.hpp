#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Actor/Enemy/KingDux/BabyDux/BuildDesc.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
    struct Builder
    {
        static void Build(ActorObj* pActor, ActorObj* parent, const BuildDesc& desc);
    };
}