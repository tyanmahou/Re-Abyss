#pragma once
#include <abyss/components/Actor/Enemy/CodeZero/Hand/KindCtrl.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    struct Builder
    {
        static void Build(ActorObj* pActor, ActorObj* parent, HandKind kind);
    };
}