#pragma once
#include <abyss/components/Actors/Enemy/CodeZero/Hand/KindCtrl.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    struct Builder
    {
        static void Build(IActor* pActor, IActor* parent, HandKind kind);
    };
}