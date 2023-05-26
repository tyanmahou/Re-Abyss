#include <abyss/scenes/Scene/DevPortal/Booter.hpp>
#if ABYSS_DEVELOP
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/modules/Sfx/PostEffects.hpp>
#include <abyss/modules/Sound/Sounds.hpp>
#include <abyss/modules/Fade/Fader.hpp>
#include <abyss/components/Cycle/DevPortal/Builder.hpp>
#include <abyss/components/UI/DevPortal/Builder.hpp>

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

        // UI
        {
            auto ui = pManager->getModule<UIs>();
            ui->create<UI::DevPortal::Builder>();
            ui->flush();
        }
        // Fade
        {
            pManager->getModule<Fader>()->fadeIn();
        }
        // Sound
        {
            pManager->getModule<Sounds>()->stop();
        }
        return true;
    }
}
#endif
