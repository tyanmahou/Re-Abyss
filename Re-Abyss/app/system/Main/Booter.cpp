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
    template<BootKind kind>
    Booter<kind>::Booter(Cycle::Main::IMasterObserver* pObserver) :
        m_pObserver(pObserver)
    {}
    template<BootKind kind>
    bool Booter<kind>::onBoot(Manager* pManager) const
    {
        // Cycle初期化
        auto* cycle = pManager->getModule<CycleMaster>();
        cycle->build<Cycle::Main::Builder>(m_pObserver);
        cycle->init();

        // Stage初期化
        auto* stage = pManager->getModule<Stage>();
        stage->setStageData(m_stageData);
        stage->load();

        // Temporary初期化
        auto* temporary = pManager->getModule<Temporary>();
        temporary->setTemporaryData(m_tempData);

        if constexpr (kind == BootKind::Normal) {
            if (m_initPlayer) {
                return stage->init(m_initPlayer, m_initEvent);
            } else {
                return stage->init();
            }
        } else if constexpr (kind == BootKind::Restart) {
            return stage->restart();
        } else {
            return false;
        }
    }

    template class Booter<BootKind::Normal>;
    template class Booter<BootKind::Restart>;
}
