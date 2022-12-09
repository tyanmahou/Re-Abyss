#include <abyss/scenes/Scene/StageResult/Booter.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/Sfx/PostEffects.hpp>

#include <abyss/components/Cycle/StageResult/Builder.hpp>
#include <abyss/components/Event/StageResult/Builder.hpp>

namespace abyss::Scene::StageResult
{
    Booter::Booter(Cycle::StageResult::IMasterObserver* pObserver) :
        m_pObserver(pObserver)
    {}

    bool Booter::onBoot(Manager* pManager) const
    {
        // Cycle初期化
        {
            auto* pCycle = pManager->getModule<CycleMaster>();
            pCycle->build<Cycle::StageResult::Builder>(m_pObserver);
            pCycle->init();
        }

        // Mainイベント初期化
        {
            auto* pEvent = pManager->getModule<Events>();
            pEvent->create<Event::StageResult::Builder>();
            pEvent->init();
        }

        // PostEffects初期化
        pManager->getModule<PostEffects>()->init();

        return true;
    }
}
