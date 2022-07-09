#pragma once
#include <abyss/scenes/System/IBooter.hpp>
#include <abyss/components/Cycle/StageResult/Master.hpp>

namespace abyss::Scene::StageResult
{
    class Booter final :
        public Sys::IBooter
    {
    public:
        Booter(Cycle::StageResult::IMasterObserver* pObserver);
        bool onBoot(Manager* pManager) const override;
    private:
        Cycle::StageResult::IMasterObserver* m_pObserver;
    };
}
