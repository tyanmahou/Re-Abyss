#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/entities/Actor/Land/LandEntity.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Actor::Land
{
    template<LandType T>
    struct BuilderFromEntity
    {
        [[REFLECTION(Build)]]
        static void Build(ActorObj* pActor, const LandEntity& entity);
    };
}
