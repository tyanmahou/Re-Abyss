#include <abyss/scenes/Scene/Title/Booter.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Cron/Crons.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/Env/Environment.hpp>
#include <abyss/modules/Sfx/PostEffects.hpp>

#include <abyss/components/Cron/BubbleGenerator/Builder.hpp>
#include <abyss/components/Cycle/Title/Builder.hpp>
#include <abyss/components/Event/Title/Builder.hpp>

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
        pManager->getModule<Events>()->create<Event::Title::Builder>();
        pManager->getModule<Events>()->init();


        // 泡
        pManager->getModule<Crons>()->create<Cron::BubbleGenerator::BuildOnce>();

        // Env初期化
        pManager->getModule<Environment>()->init(Env::EnvDesc{
            .useCaustics = true,
        });

        // PostEffects初期化
        pManager->getModule<PostEffects>()->init(Sfx::PostEffectsDesc::CreateTitle());

        return true;
    }
}
