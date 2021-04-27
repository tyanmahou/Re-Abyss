#pragma once
#include <abyss/modules/Actors/base/ActorObj.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss::Actor::Player::Shot
{
    struct Builder
    {
        static void Build(ActorObj*pActor, const s3d::Vec2& pos, Forward forward, double charge);
    };
}