#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/entities/Actor/Gimmick/BushEntity.hpp>

namespace abyss::Actor::Gimmick::Bush
{
    struct Builder
    {
        static void Build(ActorObj* pActor, const BushEntity& entity);
    };
}