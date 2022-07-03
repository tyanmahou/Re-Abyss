#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Actor/Enemy/KingDux/BabyDux/BuildDesc.hpp>
#include <abyss/entities/Actor/Enemy/BabyDuxEntity.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
    struct Builder
    {
        static void Build(ActorObj* pActor, ActorObj* parent, const BuildDesc& desc);
        static void Build(ActorObj* pActor, const BabyDuxEntity& entity);
    };
}
