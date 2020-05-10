#include "ActorUtils.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/controllers/Actors/Player/PlayerActor.hpp>

namespace abyss::ActorUtils
{
    s3d::Vec2 PlayerDiffVec(const IActor& actor, const BodyModel& body)
    {
        return actor.getModule<Player::PlayerActor>()->getPos() - body.getPos();
    }
    bool IsPlayerFrontByDistance(const IActor& actor, const BodyModel& body, double range)
    {
        s3d::Vec2 d = PlayerDiffVec(actor, body);
        double f = body.isForward(Forward::Right) ? 1.0 : -1.0;
        return f * d.x > 0 && d.length() <= range;
    }
    TimerEx CreateTimer(const IActor& actor, double sec, bool start)
    {
        return TimerEx(sec, start, [&] {return actor.getTime(); });
    }
}
