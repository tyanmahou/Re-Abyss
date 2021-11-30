#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/entities/Actor/Enemy/KingDuxEntity.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
    struct Builder
    {
        static void Build(ActorObj* pActor, ActorObj* parent);
    };
}