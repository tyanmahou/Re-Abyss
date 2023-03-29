#pragma once
#include <abyss/scenes/Sys/IBooter.hpp>
#include <abyss/components/Cycle/Splash/Master.hpp>

namespace abyss::Scene::Splash
{
    class Booter final :
        public Sys::IBooter
    {
    public:
        Booter(Cycle::Splash::IMasterObserver* pObserver);
        bool onBoot(Manager* pManager) const override;
    private:
        Cycle::Splash::IMasterObserver* m_pObserver;
    };
}
