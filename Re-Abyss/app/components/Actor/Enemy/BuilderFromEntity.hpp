#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/entities/Actor/Enemy/EnemyEntity.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Actor::Enemy
{
    template<EnemyType T>
    struct BuilderFromEntity
    {
        [[REFLECTION(Build)]]
        static void Build(ActorObj* pActor, const EnemyEntity& entity);
    };
}
