#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/entities/Actor/Gimmick/DoorEntity.hpp>

namespace abyss::Actor::Gimmick::Door
{
    struct Builder
    {
        static void Build(ActorObj* pActor, const DoorEntity& entity);
    };
}
