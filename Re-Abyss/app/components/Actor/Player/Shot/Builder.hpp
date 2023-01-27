#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/values/Forward.hpp>

namespace abyss::Actor::Player::Shot
{
    struct Builder
    {
        static void Build(ActorObj*pActor, const s3d::Vec2& pos, Forward forward, double charge);
    };
}
