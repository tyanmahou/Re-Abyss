#include <abyss/components/Cycle/Title/Builder.hpp>
#include <abyss/modules/Cycle/base/CycleObj.hpp>

namespace abyss::Cycle::Title
{
    void Builder::Build(CycleObj* pCycleObj, IMasterObserver* observer)
    {
        pCycleObj->attach<Master>(observer);
    }
}