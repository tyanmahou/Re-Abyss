#pragma once
#include <abyss/scenes/Sys/IBooter.hpp>
#include <abyss/components/Cycle/StageResult/Master.hpp>

namespace abyss::Scene::StageResult
{
    class Booter final :
        public Sys2::IBooter
    {
    public:
        Booter(Cycle::StageResult::IMasterObserver* pObserver);
        bool onBoot(const Manager* pManager) const override;
    private:
        Cycle::StageResult::IMasterObserver* m_pObserver;
    };
}
