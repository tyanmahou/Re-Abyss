#include "Builder.hpp"

#include <abyss/modules/Event/base/IEvent.hpp>
#include <abyss/components/Event/Splash/MainStream.hpp>

namespace abyss::Event::Splash
{
    void Builder::Build(IEvent* pEvent)
    {
        // メイン
        {
            pEvent->attach<MainStream>(pEvent);
        }
    }
}