#include <abyss/components/Event/SaveSelect/Builder.hpp>

#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/components/Event/SaveSelect/MainStream.hpp>

namespace abyss::Event::SaveSelect
{
    void Builder::Build(EventObj* pEvent)
    {
        // メイン
        {
            pEvent->attach<MainStream>(pEvent);
        }
    }
}