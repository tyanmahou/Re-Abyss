#include "Builder.hpp"
#include <abyss/modules/Event/base/IEvent.hpp>
#include <abyss/components/Events/GameReady/MainStream.hpp>
#include <abyss/components/Events/Common/FadeIrisOut.hpp>

namespace abyss::Event::GameReady
{
    void Builder::Build(IEvent* pEvent)
    {
        // メイン
        {
            pEvent->attach<MainStream>(pEvent);
        }
        // フェード制御
        {
            pEvent->attach<FadeIrisOut>(pEvent);
        }
    }
}