#include <abyss/scenes/Scene/Home/Booter.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/Sfx/PostEffects.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/modules/Fade/Fader.hpp>
#include <abyss/modules/Sound/Sounds.hpp>
#include <abyss/components/Cycle/Home/Builder.hpp>
#include <abyss/components/UI/Home/Top/Builder.hpp>

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

        // UI初期化
        pManager->getModule<UIs>()->create<UI::Home::Top::Builder>();
        pManager->getModule<UIs>()->flush();

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
