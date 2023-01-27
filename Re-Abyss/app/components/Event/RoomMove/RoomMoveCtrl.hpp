#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Event/base/IStream.hpp>
#include <abyss/components/Event/RoomMove/IRoomMoveCallback.hpp>
#include <abyss/modules/Room/RoomData.hpp>

namespace abyss::Event::RoomMove
{
    class IRoomMoveCallback;

    class RoomMoveCtrl :
        public IComponent,
        public IStream
    {
    public:
        RoomMoveCtrl(
            EventObj* pEvent, 
            std::unique_ptr<IRoomMoveCallback> callback,
            const Room::RoomData& nextRoom,
            double animeMilliSec
        );

        void setup(Executer executer) override;
        void onStart() override;
        void onEnd() override;

        Coro::Fiber<> onExecute() override;

    private:
        EventObj* m_pEvent;
        std::unique_ptr<IRoomMoveCallback> m_callback;
        Room::RoomData m_nextRoom;
        double m_animeMilliSec = 0;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Event::RoomMove::RoomMoveCtrl>
    {
        using Base = MultiComponents<
            Event::IStream
        >;
    };
}
