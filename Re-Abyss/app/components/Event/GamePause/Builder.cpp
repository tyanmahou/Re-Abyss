#include "Builder.hpp"
#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/components/Event/GamePause/MainStream.hpp>

namespace abyss::Event::GamePause
{
    void Builder::Build(EventObj* pEvent)
    {
        // メイン
        {
            pEvent->attach<MainStream>(pEvent);
        }
        // 
    }
}