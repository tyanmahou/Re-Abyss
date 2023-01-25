#pragma once
#if ABYSS_DEVELOP
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/Cycle/DevPortal/Master.hpp>

namespace abyss::Cycle::DevPortal
{
    struct Builder
    {
        static void Build(CycleObj* pCycleObj, IMasterObserver* observer);
    };
}
#endif
