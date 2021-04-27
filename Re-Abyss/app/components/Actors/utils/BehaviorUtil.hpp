#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>

#include <Siv3D/Fwd.hpp>
#include <Siv3D/Duration.hpp>

namespace abyss::Actor::BehaviorUtils
{
    [[nodiscard]] Coro::Task<> WaitForSeconds(ActorObj* pActor, double sec);
    [[nodiscard]] Coro::Task<> WaitForSeconds(ActorObj* pActor, s3d::Duration duration);
}