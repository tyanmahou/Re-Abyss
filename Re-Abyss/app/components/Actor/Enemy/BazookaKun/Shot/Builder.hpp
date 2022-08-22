#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Actor::Enemy::BazookaKun::Shot
{
    struct Builder
    {
        static void Build(ActorObj* pActor, const s3d::Vec2& pos, const s3d::Vec2& dir);
    };
}
