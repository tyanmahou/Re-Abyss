#include <abyss/components/Event/StageResult/Builder.hpp>

#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/components/Event/StageResult/MainStream.hpp>

namespace abyss::Event::StageResult
{
    void Builder::Build(EventObj* pEvent)
    {
        // メイン
        {
            pEvent->attach<MainStream>(pEvent);
        }
    }
}
