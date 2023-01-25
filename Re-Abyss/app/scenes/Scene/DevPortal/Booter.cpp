#include <abyss/scenes/Scene/DevPortal/Booter.hpp>
#if ABYSS_DEVELOP
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/Sfx/PostEffects.hpp>
#include <abyss/components/Cycle/DevPortal/Builder.hpp>

namespace abyss::Scene::DevPortal
{
    Booter::Booter(Cycle::DevPortal::IMasterObserver* pObserver) :
        m_pObserver(pObserver)
    {}

    bool Booter::onBoot(Manager* pManager) const
    {
        // Cycle初期化
        pManager->getModule<CycleMaster>()->build<Cycle::DevPortal::Builder>(m_pObserver);
        pManager->getModule<CycleMaster>()->init();

        // PostEffects初期化
        pManager->getModule<PostEffects>()->init();
        return true;
    }
}
#endif
