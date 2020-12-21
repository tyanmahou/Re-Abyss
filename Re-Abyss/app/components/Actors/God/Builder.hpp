#pragma once
#include <abyss/modules/Actors/base/IActor.hpp>

namespace abyss::Actor::God
{
    struct Builder
    {
        static void Build(IActor* pActor);
    };
}