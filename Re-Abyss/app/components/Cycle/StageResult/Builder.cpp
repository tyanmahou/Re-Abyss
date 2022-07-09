#include <abyss/components/Cycle/StageResult/Builder.hpp>
#include <abyss/modules/Cycle/base/CycleObj.hpp>

namespace abyss::Cycle::StageResult
{
    void Builder::Build(CycleObj* pCycleObj, IMasterObserver* observer)
    {
        pCycleObj->attach<Master>(observer);
    }
}
