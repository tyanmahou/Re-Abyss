#pragma once
#include <abyss/scenes/System/IBooter.hpp>
#include <abyss/components/Cycle/Title/Master.hpp>

namespace abyss::Scene::Title
{
    class Booter final :
        public Sys::IBooter
    {
    public:
        Booter(Cycle::Title::IMasterObserver* pObserver);
        bool onBoot(Manager* pManager) const override;
    private:
        Cycle::Title::IMasterObserver* m_pObserver;
    };
}
