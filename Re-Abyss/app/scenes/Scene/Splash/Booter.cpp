#include <abyss/scenes/Scene/Splash/Booter.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/modules/Sfx/PostEffects.hpp>

#include <abyss/components/Cycle/Splash/Builder.hpp>
#include <abyss/components/UI/Splash/Builder.hpp>

namespace abyss::Scene::Splash
{
    Booter::Booter(Cycle::Splash::IMasterObserver* pObserver) :
        m_pObserver(pObserver)
    {}
    bool Booter::onBoot(Manager* pManager) const
    {
        // Cycle初期化
        pManager->getModule<CycleMaster>()->build<Cycle::Splash::Builder>(m_pObserver);
        pManager->getModule<CycleMaster>()->init();

        // UI初期化
        pManager->getModule<UIs>()->create<UI::Splash::Builder>();
        pManager->getModule<UIs>()->flush();

        // PostEffects初期化
        pManager->getModule<PostEffects>()->init();

        return true;
    }
}
