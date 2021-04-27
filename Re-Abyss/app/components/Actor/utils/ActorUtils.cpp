#include "ActorUtils.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>

namespace abyss::Actor::ActorUtils
{
    const s3d::Vec2& PlayerPos(const ActorObj& actor)
    {
        return actor.getModule<Actor::Player::PlayerManager>()->getPos();
    }
    s3d::Vec2 PlayerDiffVec(const ActorObj& actor, const Body& body)
    {
        return PlayerPos(actor) - body.getPos();
    }
    bool IsPlayerFrontByDistance(const ActorObj& actor, const Body& body, double range)
    {
        s3d::Vec2 d = PlayerDiffVec(actor, body);
        double f = body.isForward(Forward::Right) ? 1.0 : -1.0;
        return f * d.x > 0 && d.length() <= range;
    }
    TimerEx CreateTimer(const ActorObj& actor, double sec, bool start)
    {
        return TimerEx(sec, start, [&] {return actor.getUpdateTime(); });
    }
}