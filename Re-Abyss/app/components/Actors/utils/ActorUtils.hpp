#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Fwd.hpp>
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss::Actor::ActorUtils
{
    const s3d::Vec2& PlayerPos(const IActor& actor);

    s3d::Vec2 PlayerDiffVec(const IActor& actor, const Body& body);
    bool IsPlayerFrontByDistance(const IActor& actor, const Body& body, double range);

    TimerEx CreateTimer(const IActor& actor, double sec, bool start = true);
}