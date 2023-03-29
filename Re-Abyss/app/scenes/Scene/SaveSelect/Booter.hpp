#pragma once
#include <abyss/scenes/Sys/IBooter.hpp>
#include <abyss/components/Cycle/SaveSelect/Master.hpp>

namespace abyss::Scene::SaveSelect
{
    class Booter final :
        public Sys2::IBooter
    {
    public:
        Booter(Cycle::SaveSelect::IMasterObserver* pObserver);
        bool onBoot(Manager* pManager) const override;
    private:
        Cycle::SaveSelect::IMasterObserver* m_pObserver;
    };
}
