#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss::Actor::ActorUtils
{
    const s3d::Vec2& PlayerPos(const ActorObj& actor);

    s3d::Vec2 ToPlayer(const ActorObj& actor, const Body& body);
    bool IsPlayerFrontByDistance(const ActorObj& actor, const Body& body, double range);
}