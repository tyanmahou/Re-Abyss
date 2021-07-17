#include "Booter.hpp"
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>

#include <abyss/components/Cycle/Splash/Builder.hpp>

namespace abyss::Sys::Splash
{
    Booter::Booter(Cycle::Splash::IMasterObserver* pObserver) :
        m_pObserver(pObserver)
    {}
    bool Booter::onBoot(Manager* pManager) const
    {
        pManager->getModule<CycleMaster>()->build<Cycle::Splash::Builder>(m_pObserver);
        return true;
    }
}
