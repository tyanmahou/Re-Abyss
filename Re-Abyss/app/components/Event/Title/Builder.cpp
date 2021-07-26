#include "Builder.hpp"

#include <abyss/modules/Event/base/IEvent.hpp>
#include <abyss/components/Event/Title/MainStream.hpp>
#include <abyss/components/Event/Title/BgmCtrl.hpp>

namespace abyss::Event::Title
{
    void Builder::Build(IEvent* pEvent)
    {
        // メイン
        {
            pEvent->attach<MainStream>(pEvent);
        }
        // Bgm
        {
            pEvent->attach<BgmCtrl>(pEvent);
        }
    }
}