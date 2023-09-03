#include <abyss/components/Cycle/Experiment/Builder.hpp>
#if ABYSS_DEVELOP
#include <abyss/modules/Cycle/base/CycleObj.hpp>

namespace abyss::Cycle::Experiment
{
    void Builder::Build(CycleObj* pCycleObj, IMasterObserver* observer)
    {
        pCycleObj->attach<Master>(observer);
    }
}
#endif
