#include <abyss/components/Cycle/Main/Builder.hpp>
#include <abyss/modules/Cycle/base/CycleObj.hpp>

namespace abyss::Cycle::Main
{
    void Builder::Build(CycleObj* pCycleObj, IMasterObserver* observer)
    {
        pCycleObj->attach<Master>(observer);
    }
}