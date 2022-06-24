#pragma once
#include <abyss/scenes/System/IBooter.hpp>
#include <abyss/components/Cycle/Main/Master.hpp>

namespace abyss::Scene::Stage
{
    enum class BootKind
    {
        Normal,
        Restart,
    };

    template<BootKind kind = BootKind::Normal>
    class Booter final :
        public Sys::IBooter
    {
    public:
        Booter(Cycle::Main::IMasterObserver* pObserver);

        bool onBoot(Manager* pManager) const override;

        Booter& setInitPlayer(std::shared_ptr<Actor::ActorObj> player)
        {
            m_initPlayer = player;
            return *this;
        }
        Booter& setInitEvent(std::shared_ptr<Event::EventObj> event)
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
        Booter& setCharaTable(std::shared_ptr<Novel::CharaTable> charaTable)
        {
            m_charaTable = charaTable;
            return *this;
        }
    private:
        Cycle::Main::IMasterObserver* m_pObserver;

        std::shared_ptr<Actor::ActorObj> m_initPlayer;
        std::shared_ptr<Event::EventObj> m_initEvent;
        std::shared_ptr<StageData> m_stageData;
        std::shared_ptr<TemporaryData> m_tempData;
        std::shared_ptr<Novel::CharaTable> m_charaTable;
    };

    using BooterNormal = Booter<BootKind::Normal>;
    using BooterRestart = Booter<BootKind::Restart>;
}