#pragma once
#include <abyss/scenes/Sys/IBooter.hpp>
#include <abyss/components/Cycle/Title/Master.hpp>

namespace abyss::Scene::Title
{
    class Booter final :
        public Sys2::IBooter
    {
    public:
        Booter(Cycle::Title::IMasterObserver* pObserver);
        bool onBoot(const Manager* pManager) const override;
    private:
        Cycle::Title::IMasterObserver* m_pObserver;
    };
}
