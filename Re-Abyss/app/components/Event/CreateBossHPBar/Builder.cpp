#include "Builder.hpp"
#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/components/Event/CreateBossHPBar/MainStream.hpp>

namespace abyss::Event::CreateBossHPBar
{
    void Builder::Build(EventObj* pEvent, const Ref<UI::UIObj>& hpBar)
    {
        // メイン
        {
            pEvent->attach<MainStream>(pEvent, hpBar);
        }
        // 
    }
}