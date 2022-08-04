#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/entities/Actor/Gimmick/GimmickEntity.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Actor::Gimmick
{
    template<GimmickType T>
    struct BuilderFromEntity
    {
        [[REFLECTION(Build)]]
        static void Build(ActorObj* pActor, const GimmickEntity& entity);
    };
}
