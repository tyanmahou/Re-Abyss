#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::ActorUtils
{
    bool IsPlayerFrontByDistance(const IActor& actor, const BodyModel& body, double range);
}