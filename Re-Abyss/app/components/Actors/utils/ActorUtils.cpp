#include "ActorUtils.hpp"
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/modules/Actors/Player/PlayerManager.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>

namespace abyss::Actor::ActorUtils
{
    const s3d::Vec2& PlayerPos(const IActor& actor)
    {
        return actor.getModule<Actor::Player::PlayerManager>()->getPos();
    }
    s3d::Vec2 PlayerDiffVec(const IActor& actor, const Body& body)
    {
        return PlayerPos(actor) - body.getPos();
    }
    bool IsPlayerFrontByDistance(const IActor& actor, const Body& body, double range)
    {
        s3d::Vec2 d = PlayerDiffVec(actor, body);
        double f = body.isForward(Forward::Right) ? 1.0 : -1.0;
        return f * d.x > 0 && d.length() <= range;
    }
    TimerEx CreateTimer(const IActor& actor, double sec, bool start)
    {
        return TimerEx(sec, start, [&] {return actor.getUpdateTime(); });
    }
}
