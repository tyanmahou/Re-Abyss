#include "Builder.hpp"
#include <abyss/modules/Event/base/IEvent.hpp>
#include <abyss/components/Events/CreateBossHPBar/MainStream.hpp>

namespace abyss::Event::CreateBossHPBar
{
    void Builder::Build(IEvent* pEvent, const Ref<ui::IUserInterface>& hpBar)
    {
        // メイン
        {
            pEvent->attach<MainStream>(pEvent, hpBar);
        }
        // 
    }
}