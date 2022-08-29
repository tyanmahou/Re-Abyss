#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/entities/Actor/Gimmick/ShutterWallEntity.hpp>

namespace abyss::Actor::Gimmick::ShutterWall
{
    struct Builder
    {
        static void Build(ActorObj* pActor, const ShutterWallEntity& entity);
    };
}
