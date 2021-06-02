#pragma once
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor::Player::PlayerUtil
{
    /// <summary>
    /// 死んでるか
    /// </summary>
    bool IsDead(ActorObj* pActor);
}