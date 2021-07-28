#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Cycle/SaveSelect/Master.hpp>

namespace abyss::Cycle::SaveSelect
{
    struct Builder
    {
        static void Build(CycleObj* pCycleObj, IMasterObserver* observer);
    };
}