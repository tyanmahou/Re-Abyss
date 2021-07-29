#include "Booter.hpp"
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/UI/UIs.hpp>

#include <abyss/modules/Stage/Stage.hpp>
#include <abyss/modules/Temporary/Temporary.hpp>

namespace abyss::Sys::Main
{
    Booter::Booter(Cycle::Main::IMasterObserver* pObserver) :
        m_pObserver(pObserver)
    {}
    bool Booter::onBoot(Manager* pManager) const
    {
        // 事前設定
        auto* stage = pManager->getModule<Stage>();
        stage->setStageData(m_stageData);
        stage->load();

        auto* temporary = pManager->getModule<Temporary>();
        temporary->setTemporaryData(m_tempData);

        if (m_bootKind == BootKind::Init) {
            if (m_initPlayer) {
                stage->init(m_initPlayer, nullptr);
            } else {
                stage->init();
            }
        } else {
            stage->restart();
        }

        return true;
    }
}
