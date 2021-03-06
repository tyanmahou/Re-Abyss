#include "Builder.hpp"
#include <abyss/modules/Event/base/IEvent.hpp>
#include <abyss/components/Events/GamePause/MainStream.hpp>

namespace abyss::Event::GamePause
{
    void Builder::Build(IEvent* pEvent)
    {
        // メイン
        {
            pEvent->attach<MainStream>(pEvent);
        }
        // 
    }
}