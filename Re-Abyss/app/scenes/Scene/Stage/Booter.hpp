#pragma once
#include <abyss/scenes/Sys/IBooter.hpp>
#include <abyss/components/Cycle/Main/Master.hpp>
#include <abyss/components/Actor/Player/PlayerDesc.hpp>

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

        Booter& setPlayerDesc(const Actor::Player::PlayerDesc& playerDesc)
        {
            m_playerDesc = playerDesc;
            return *this;
        }
        Booter& setInitEvent(std::shared_ptr<Event::EventObj> event)
        {
            m_initEvent = event;
            return *this;
        }
    private:
        Cycle::Main::IMasterObserver* m_pObserver;

        Actor::Player::PlayerDesc m_playerDesc;
        std::shared_ptr<Event::EventObj> m_initEvent;
    };

    using BooterNormal = Booter<BootKind::Normal>;
    using BooterRestart = Booter<BootKind::Restart>;
}
