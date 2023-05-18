#include <abyss/scenes/Scene/Title/Booter.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Cron/Crons.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/modules/FieldEnv/Environment.hpp>
#include <abyss/modules/Sfx/PostEffects.hpp>
#include <abyss/modules/Fade/Fader.hpp>

#include <abyss/components/Cron/BubbleGenerator/Builder.hpp>
#include <abyss/components/Cycle/Title/Builder.hpp>
#include <abyss/components/UI/Title/Builder.hpp>

#include <Siv3D.hpp>

namespace abyss::Scene::Title
{
    Booter::Booter(Cycle::Title::IMasterObserver* pObserver) :
        m_pObserver(pObserver)
    {}
    bool Booter::onBoot(Manager* pManager) const
    {
        // Cycle初期化
        pManager->getModule<CycleMaster>()->build<Cycle::Title::Builder>(m_pObserver);
        pManager->getModule<CycleMaster>()->init();

        // Mainイベント初期化
        pManager->getModule<UIs>()->create<UI::Title::Builder>();
        pManager->getModule<UIs>()->flush();


        // 泡
        pManager->getModule<Crons>()->create<Cron::BubbleGenerator::BuildOnce>();
        // Fade
        {
            pManager->getModule<Fader>()->fadeIn();
        }
        return true;
    }
}
