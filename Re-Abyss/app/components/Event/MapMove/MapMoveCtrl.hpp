#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Event/base/IStream.hpp>
#include <abyss/components/Event/MapMove/IMapMoveCallback.hpp>
#include <abyss/components/Event/MapMove/LinkData.hpp>

namespace abyss::Event::MapMove
{
    class MapMoveCtrl :
        public IComponent,
        public IStream
    {
    public:
        MapMoveCtrl(
            EventObj* pEvent,
            std::unique_ptr<IMapMoveCallback> callback,
            const LinkData& link,
            double animeMilliSec
        );

        void setup(Executer executer) override;
        void onStart() override;
        void onEnd() override;

        Coro::Fiber<> onExecute() override;

    private:
        EventObj* m_pEvent;
        std::unique_ptr<IMapMoveCallback> m_callback;
        LinkData m_link;
        double m_animeMilliSec = 0;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Event::MapMove::MapMoveCtrl>
    {
        using Base = MultiComponents<
            Event::IStream
        >;
    };
}
