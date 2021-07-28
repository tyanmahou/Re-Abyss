#include "Builder.hpp"

#include <abyss/modules/Event/base/IEvent.hpp>
#include <abyss/components/Event/SaveSelect/MainStream.hpp>

namespace abyss::Event::SaveSelect
{
    void Builder::Build(IEvent* pEvent)
    {
        // メイン
        {
            pEvent->attach<MainStream>(pEvent);
        }
    }
}