#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Coro/Task/Task.hpp>

#include <Siv3D/Fwd.hpp>
#include <Siv3D/Duration.hpp>

namespace abyss::Actor::BehaviorUtils
{
    Coro::Task WaitForSeconds(IActor* pActor, double sec);
    Coro::Task WaitForSeconds(IActor* pActor, s3d::Duration duration);
}