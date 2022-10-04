#pragma once
#include <abyss/scenes/System/IBooter.hpp>
#include <abyss/components/Cycle/Home/Master.hpp>

namespace abyss::Scene::Home
{
    class Booter final :
        public Sys::IBooter
    {
    public:
        Booter(Cycle::Home::IMasterObserver* pObserver);
        bool onBoot(Manager* pManager) const override;
    private:
        Cycle::Home::IMasterObserver* m_pObserver;
    };
}
