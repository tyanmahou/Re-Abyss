#include "Booter.hpp"
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/UI/UIs.hpp>

#include <abyss/modules/Stage/Stage.hpp>
#include <abyss/modules/Temporary/Temporary.hpp>

#include <abyss/components/Cycle/Main/Builder.hpp>

namespace abyss::Sys::Main
{
    Booter::Booter(Cycle::Main::IMasterObserver* pObserver) :
        m_pObserver(pObserver)
    {}
    bool Booter::onBoot(Manager* pManager) const
    {
        // Cycle初期化
        auto* cycle = pManager->getModule<CycleMaster>();
        cycle->build<Cycle::Main::Builder>(m_pObserver);
        cycle->init();

        // StageLoad
        auto* stage = pManager->getModule<Stage>();
        stage->setStageData(m_stageData);
        stage->load();

        // TemporaryLoad
        auto* temporary = pManager->getModule<Temporary>();
        temporary->setTemporaryData(m_tempData);

        if (m_bootKind == BootKind::Init) {
            if (m_initPlayer) {
                stage->init(m_initPlayer, nullptr);
            } else {
                stage->init();
            }
        } else if (m_bootKind == BootKind::Restart) {
            stage->restart();
        }

        return true;
    }
}
