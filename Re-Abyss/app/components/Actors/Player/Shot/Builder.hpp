#pragma once
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss::Actor::Player::Shot
{
    struct Builder
    {
        static void Build(IActor*pActor, const s3d::Vec2& pos, Forward forward, double charge);
    };
}