#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Cycle/Main/Master.hpp>

namespace abyss::Cycle::Main
{
    struct Builder
    {
        static void Build(CycleObj* pCycleObj, IMasterObserver* observer);
    };
}