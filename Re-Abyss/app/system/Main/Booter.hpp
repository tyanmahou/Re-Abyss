#pragma once
#include <abyss/system/base/IBooter.hpp>
#include <abyss/components/Cycle/Main/Master.hpp>

namespace abyss::Sys::Main
{
    enum class BootKind
    {
        Init,
        Restart,
    };

    class Booter final :
        public IBooter
    {
    public:
        Booter(Cycle::Main::IMasterObserver* pObserver);

        bool onBoot(Manager* pManager) const override;

        Booter& setBootKind(BootKind kind)
        {
            m_bootKind = kind;
            return *this;
        }

        Booter& setInitPlayer(std::shared_ptr<Actor::ActorObj> player)
        {
            m_initPlayer = player;
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
        BootKind m_bootKind = BootKind::Init;

        std::shared_ptr<Actor::ActorObj> m_initPlayer;
        std::shared_ptr<StageData> m_stageData;
        std::shared_ptr<TemporaryData> m_tempData;
    };
}