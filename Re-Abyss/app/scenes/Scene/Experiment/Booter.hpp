#pragma once
#if ABYSS_DEVELOP
#include <abyss/scenes/Sys/IBooter.hpp>
#include <abyss/components/Cycle/Experiment/Master.hpp>

namespace abyss::Scene::Experiment
{
    class Booter final :
        public Sys::IBooter
    {
    public:
        Booter(Cycle::Experiment::IMasterObserver* pObserver, const s3d::Optional<size_t>& initTopic = s3d::none);
        bool onBoot(Manager* pManager) const override;
    private:
        Cycle::Experiment::IMasterObserver* m_pObserver;
        s3d::Optional<size_t> m_initTopic;
    };
}
#endif
