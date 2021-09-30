#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Fwd.hpp>
#include <Siv3D/Timer.hpp>

namespace abyss::Actor::ActorUtils
{
    const s3d::Vec2& PlayerPos(const ActorObj& actor);

    s3d::Vec2 PlayerDiffVec(const ActorObj& actor, const Body& body);
    bool IsPlayerFrontByDistance(const ActorObj& actor, const Body& body, double range);
}