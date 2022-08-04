#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/entities/Actor/Item/ItemEntity.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Actor::Item
{
    template<ItemType T>
    struct BuilderFromEntity
    {
        [[REFLECTION(Build)]]
        static void Build(ActorObj* pActor, const ItemEntity& entity);
    };
}
