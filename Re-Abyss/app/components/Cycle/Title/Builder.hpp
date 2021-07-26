#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Cycle/Title/Master.hpp>

namespace abyss::Cycle::Title
{
    struct Builder
    {
        static void Build(CycleObj* pCycleObj, IMasterObserver* observer);
    };
}