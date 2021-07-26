#include "Booter.hpp"
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/Event/Events.hpp>

#include <abyss/components/Cycle/Title/Builder.hpp>
#include <abyss/components/Event/Title/Builder.hpp>

namespace abyss::Sys::Title
{
    Booter::Booter(Cycle::Title::IMasterObserver* pObserver) :
        m_pObserver(pObserver)
    {}
    bool Booter::onBoot(Manager* pManager) const
    {
        // Cycle初期化
        pManager->getModule<CycleMaster>()->build<Cycle::Title::Builder>(m_pObserver);
        pManager->getModule<CycleMaster>()->init();

        // Mainイベント初期化
        pManager->getModule<Events>()->create<Event::Title::Builder>();
        pManager->getModule<Events>()->init();

        return true;
    }
}
