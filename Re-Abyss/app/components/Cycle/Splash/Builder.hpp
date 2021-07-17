#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Cycle/Splash/Master.hpp>

namespace abyss::Cycle::Splash
{
    struct Builder
    {
        static void Build(CycleObj* pCycleObj, IMasterObserver* observer);
    };
}