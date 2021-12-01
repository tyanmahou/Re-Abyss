#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/BuildDesc.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
    struct Builder
    {
        static void Build(ActorObj* pActor, ActorObj* parent, const BuildDesc& desc);
    };
}