#include <abyss/components/Event/Splash/Builder.hpp>

#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/components/Event/Splash/MainStream.hpp>

namespace abyss::Event::Splash
{
    void Builder::Build(EventObj* pEvent)
    {
        // メイン
        {
            pEvent->attach<MainStream>(pEvent);
        }
    }
}