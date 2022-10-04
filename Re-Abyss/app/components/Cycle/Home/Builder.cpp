#include <abyss/components/Cycle/Home/Builder.hpp>
#include <abyss/modules/Cycle/base/CycleObj.hpp>

namespace abyss::Cycle::Home
{
    void Builder::Build(CycleObj* pCycleObj, IMasterObserver* observer)
    {
        pCycleObj->attach<Master>(observer);
    }
}
