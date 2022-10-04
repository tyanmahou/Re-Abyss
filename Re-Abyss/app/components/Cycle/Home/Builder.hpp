#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Cycle/Home/Master.hpp>

namespace abyss::Cycle::Home
{
    struct Builder
    {
        static void Build(CycleObj* pCycleObj, IMasterObserver* observer);
    };
}
