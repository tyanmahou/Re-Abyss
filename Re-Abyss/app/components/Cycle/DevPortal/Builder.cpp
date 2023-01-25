#include <abyss/components/Cycle/DevPortal/Builder.hpp>
#if ABYSS_DEVELOP
#include <abyss/modules/Cycle/base/CycleObj.hpp>

namespace abyss::Cycle::DevPortal
{
    void Builder::Build(CycleObj* pCycleObj, IMasterObserver* observer)
    {
        pCycleObj->attach<Master>(observer);
    }
}
#endif
