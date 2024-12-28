#pragma once
#include <abyss/components/Actor/Player/State/BaseState.hpp>
#include <abyss/components/Actor/Gimmick/Door/DoorData.hpp>
#include <abyss/modules/Room/RoomData.hpp>

namespace abyss::Actor::Player
{
    class DoorInState final : public BaseState
    {
    public:
        static void Change(
            ActorObj* player,
            const Gimmick::Door::DoorData& door,
            const Room::RoomData& room
        );
    public:
        DoorInState(const Gimmick::Door::DoorData& door, const Room::RoomData& room);
    private:
        void start() override;
        void end() override;
        void update()override;
    private:
        Gimmick::Door::DoorData m_door;
        Room::RoomData m_room;
    };
}
