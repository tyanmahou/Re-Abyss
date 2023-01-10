#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Actor/Actors.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/components/Actor/Common/Body.hpp>

namespace abyss::Actor::ActorUtils
{
    const s3d::Vec2& PlayerPos(const ActorObj& actor)
    {
        return actor.getModule<Actor::Player::PlayerManager>()->getPos();
    }
    const s3d::Vec2& PlayerVelocity(const ActorObj& actor)
    {
        return actor.getModule<Actor::Player::PlayerManager>()->getVelocity();
    }
    s3d::Vec2 ToPlayer(const ActorObj& actor, const Body& body)
    {
        return PlayerPos(actor) - body.getPos();
    }
    bool IsPlayerFrontByDistance(const ActorObj& actor, const Body& body, double range)
    {
        s3d::Vec2 d = ToPlayer(actor, body);
        double f = body.isForward(Forward::Right) ? 1.0 : -1.0;
        return f * d.x > 0 && d.length() <= range;
    }
}
