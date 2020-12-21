#pragma once
#include <abyss/modules/Actors/base/IActor.hpp>

namespace abyss::Actor::Ooparts::Nyan
{
    struct Builder
    {
        static void Build(IActor* pActor, IActor* parent);
    };
}