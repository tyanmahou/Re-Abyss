#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/entities/Actor/Gimmick/BulletinEntity.hpp>

namespace abyss::Actor::Gimmick::Bulletin
{
    struct Builder
    {
        static void Build(ActorObj* pActor, const BulletinEntity& entity);
    };
}