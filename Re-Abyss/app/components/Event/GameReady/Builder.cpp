#include <abyss/components/Event/GameReady/Builder.hpp>
#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/components/Event/GameReady/MainStream.hpp>
#include <abyss/components/Event/Common/FadeIrisOut.hpp>

namespace abyss::Event::GameReady
{
    void Builder::Build(EventObj* pEvent)
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