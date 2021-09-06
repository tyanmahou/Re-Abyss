#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/entities/Actor/Enemy/WarrusEntity.hpp>

namespace abyss::Actor::Enemy::Warrus
{
    struct Builder
    {
        static void Build(ActorObj* pActor, const WarrusEntity& entity);
    };
}