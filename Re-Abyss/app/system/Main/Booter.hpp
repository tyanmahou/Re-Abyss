#pragma once
#include <abyss/system/base/IBooter.hpp>
#include <abyss/components/Cycle/Main/Master.hpp>

namespace abyss::Sys::Main
{
    enum class BootKind
    {
        Normal,
        Restart,
    };

    template<BootKind kind = BootKind::Normal>
    class Booter final :
        public IBooter
    {
    public:
        Booter(Cycle::Main::IMasterObserver* pObserver);

        bool onBoot(Manager* pManager) const override;

        Booter& setInitPlayer(std::shared_ptr<Actor::ActorObj> player)
        {
            m_initPlayer = player;
            return *this;
        }
        Booter& setInitEvent(std::shared_ptr<Event::IEvent> event)
        {
            m_initEvent = event;
            return *this;
        }

        Booter& setStageData(std::shared_ptr<StageData> stageData)
        {
            m_stageData = stageData;
            return *this;
        }
        Booter& setTempData(std::shared_ptr<TemporaryData> tempData)
        {
            m_tempData = tempData;
            return *this;
        }
    private:
        Cycle::Main::IMasterObserver* m_pObserver;

        std::shared_ptr<Actor::ActorObj> m_initPlayer;
        std::shared_ptr<Event::IEvent> m_initEvent;
        std::shared_ptr<StageData> m_stageData;
        std::shared_ptr<TemporaryData> m_tempData;
    };

    using BooterNormal = Booter<BootKind::Normal>;
    using BooterRestart = Booter<BootKind::Restart>;
}