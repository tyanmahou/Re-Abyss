#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>

namespace abyss::Actor::Ooparts::Xto
{
    struct Builder
    {
        static void Build(IActor* pActor, IActor* parent);
    };
}