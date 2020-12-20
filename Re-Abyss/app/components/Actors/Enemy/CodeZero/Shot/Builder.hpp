#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    struct Builder
    {
        static void Build(IActor* pActor, IActor* parent);
    };
}