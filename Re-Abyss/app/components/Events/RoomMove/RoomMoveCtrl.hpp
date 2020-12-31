#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Events/base/IStream.hpp>
#include <abyss/components/Events/RoomMove/IRoomMoveCallback.hpp>
#include <abyss/models/Room/RoomModel.hpp>

namespace abyss::Event::RoomMove
{
    class IRoomMoveCallback;

    class RoomMoveCtrl :
        public IComponent,
        public IStream
    {
    public:
        RoomMoveCtrl(
            IEvent* pEvent, 
            std::unique_ptr<IRoomMoveCallback> callback,
            const RoomModel& nextRoom,
            double animeMilliSec
        );

        void setup(Executer executer) override;
        void onStart() override;
        void onEnd() override;

        Coro::Task<> onExecute() override;

    private:
        IEvent* m_pEvent;
        std::unique_ptr<IRoomMoveCallback> m_callback;
        RoomModel m_nextRoom;
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