#pragma once
#include <abyss/scenes/Sys/IBooter.hpp>
#include <abyss/components/Cycle/Home/Master.hpp>

namespace abyss::Scene::Home
{
    class Booter final :
        public Sys2::IBooter
    {
    public:
        Booter(Cycle::Home::IMasterObserver* pObserver);
        bool onBoot(const Manager* pManager) const override;
    private:
        Cycle::Home::IMasterObserver* m_pObserver;
    };
}
