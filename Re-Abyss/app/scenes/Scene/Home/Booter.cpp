#include <abyss/scenes/Scene/Home/Booter.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/Sfx/PostEffects.hpp>
#include <abyss/components/Cycle/Home/Builder.hpp>

namespace abyss::Scene::Home
{
    Booter::Booter(Cycle::Home::IMasterObserver* pObserver) :
        m_pObserver(pObserver)
    {}

    bool Booter::onBoot(Manager* pManager) const
    {
        // Cycle初期化
        pManager->getModule<CycleMaster>()->build<Cycle::Home::Builder>(m_pObserver);
        pManager->getModule<CycleMaster>()->init();

        // PostEffects初期化
        pManager->getModule<PostEffects>()->init();
        return true;
    }
}
