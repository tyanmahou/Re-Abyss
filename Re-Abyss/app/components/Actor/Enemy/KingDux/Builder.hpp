#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/entities/Actor/Enemy/KingDuxEntity.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    struct Builder
    {
        static void Build(ActorObj* pActor, const KingDuxEntity& entity);
    };
}