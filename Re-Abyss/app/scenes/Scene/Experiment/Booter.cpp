#include <abyss/scenes/Scene/Experiment/Booter.hpp>
#if ABYSS_DEVELOP
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/modules/Sfx/PostEffects.hpp>
#include <abyss/modules/Sound/Sounds.hpp>
#include <abyss/modules/Fade/Fader.hpp>
#include <abyss/components/Cycle/Experiment/Builder.hpp>
#include <abyss/components/UI/Experiment/Builder.hpp>

namespace abyss::Scene::Experiment
{
    Booter::Booter(Cycle::Experiment::IMasterObserver* pObserver, const s3d::Optional<size_t>& initTopic) :
        m_pObserver(pObserver),
        m_initTopic(initTopic)
    {}

    bool Booter::onBoot(Manager* pManager) const
    {
        // Cycle初期化
        pManager->getModule<CycleMaster>()->build<Cycle::Experiment::Builder>(m_pObserver);
        pManager->getModule<CycleMaster>()->init();

        // UI
        {
            auto ui = pManager->getModule<UIs>();
            ui->create<UI::Experiment::Builder>(m_initTopic);
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
