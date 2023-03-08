#include <abyss/scenes/Scene/SaveSelect/Booter.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/modules/Sfx/PostEffects.hpp>

#include <abyss/components/Cycle/SaveSelect/Builder.hpp>
#include <abyss/components/UI/SaveSelect/Main/Builder.hpp>

namespace abyss::Scene::SaveSelect
{
    Booter::Booter(Cycle::SaveSelect::IMasterObserver* pObserver) :
        m_pObserver(pObserver)
    {}
    bool Booter::onBoot(Manager* pManager) const
    {
        // Cycle初期化
        pManager->getModule<CycleMaster>()->build<Cycle::SaveSelect::Builder>(m_pObserver);
        pManager->getModule<CycleMaster>()->init();

        // UI初期化
        pManager->getModule<UIs>()->create<UI::SaveSelect::Main::Builder>();
        pManager->getModule<UIs>()->flush();

        // PostEffects初期化
        pManager->getModule<PostEffects>()->init();

        return true;
    }
}
