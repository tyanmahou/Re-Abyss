#include <abyss/scenes/Scene/StageResult/Booter.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/modules/Sfx/PostEffects.hpp>

#include <abyss/components/Cycle/StageResult/Builder.hpp>
#include <abyss/components/UI/StageResult/Builder.hpp>

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
            auto* pUi = pManager->getModule<UIs>();
            pUi->create<UI::StageResult::Builder>();
            pUi->flush();
        }

        return true;
    }
}
