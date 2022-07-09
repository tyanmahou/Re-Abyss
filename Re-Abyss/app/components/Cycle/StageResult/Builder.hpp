#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Cycle/StageResult/Master.hpp>

namespace abyss::Cycle::StageResult
{
    struct Builder
    {
        static void Build(CycleObj* pCycleObj, IMasterObserver* observer);
    };
}
