#include "ActorUtils.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>

namespace abyss::ActorUtils
{
    bool IsPlayerFrontByDistance(const IActor& actor, const BodyModel& body, double range)
    {
        s3d::Vec2 d = actor.getWorld()->getPlayerPos() - body.getPos();
        double f = body.isForward(Forward::Right) ? 1.0 : -1.0;
        return f * d.x > 0 && d.length() <= range;
    }
}
