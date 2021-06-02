#include "PlayerUtil.hpp"

#include <abyss/components/Actor/Commons/HP.hpp>
#include <abyss/components/Actor/Player/StateChecker.hpp>

namespace abyss::Actor::Player::PlayerUtil
{
    bool IsDead(ActorObj* pActor)
    {
        return pActor->find<HP>()->isDead() || pActor->find<StateChecker>()->isDeadState();
    }
}
