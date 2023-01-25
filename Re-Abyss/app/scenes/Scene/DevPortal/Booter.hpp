#pragma once
#if ABYSS_DEVELOP
#include <abyss/scenes/System/IBooter.hpp>
#include <abyss/components/Cycle/DevPortal/Master.hpp>

namespace abyss::Scene::DevPortal
{
    class Booter final :
        public Sys::IBooter
    {
    public:
        Booter(Cycle::DevPortal::IMasterObserver* pObserver);
        bool onBoot(Manager* pManager) const override;
    private:
        Cycle::DevPortal::IMasterObserver* m_pObserver;
    };
}
#endif
