#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss::ActorUtils
{
    s3d::Vec2 PlayerDiffVec(const IActor& actor, const BodyModel& body);
    bool IsPlayerFrontByDistance(const IActor& actor, const BodyModel& body, double range);
}