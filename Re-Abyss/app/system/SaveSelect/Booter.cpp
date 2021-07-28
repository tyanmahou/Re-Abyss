#include "Booter.hpp"
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/UI/UIs.hpp>

#include <abyss/components/Cycle/SaveSelect/Builder.hpp>
#include <abyss/components/Event/SaveSelect/Builder.hpp>
#include <abyss/components/UI/SaveSelect/Panel/Builder.hpp>

namespace abyss::Sys::SaveSelect
{
    Booter::Booter(Cycle::SaveSelect::IMasterObserver* pObserver) :
        m_pObserver(pObserver)
    {}
    bool Booter::onBoot(Manager* pManager) const
    {
        // Cycle初期化
        pManager->getModule<CycleMaster>()->build<Cycle::SaveSelect::Builder>(m_pObserver);
        pManager->getModule<CycleMaster>()->init();

        // Mainイベント初期化
        pManager->getModule<Events>()->create<Event::SaveSelect::Builder>();
        pManager->getModule<Events>()->init();

        // UI初期化
        pManager->getModule<UIs>()->create<UI::SaveSelect::Panel::Builder>();
        pManager->getModule<UIs>()->flush();

        return true;
    }
}
