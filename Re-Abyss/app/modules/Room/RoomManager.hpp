#pragma once
#include <abyss/models/Room/RoomModel.hpp>

namespace abyss::Room
{
    class RoomManager
    {
    public:
        RoomManager();

        bool isOutOfRoomDeath(const s3d::Vec2& pos, double margin = 0.0) const;

        void setRoom(const RoomModel& room)
        {
            m_currentRoom = room;
        }
        const RoomModel& currentRoom() const
        {
            return m_currentRoom;
        }

        void setNextRoom(const s3d::Optional<RoomModel>& room)
        {
            m_nextRoom = room;
        }
        const s3d::Optional<RoomModel>& nextRoom() const
        {
            return m_nextRoom;
        }

        template<class T>
        bool isInRoom(const T& shape)const
        {
            return m_currentRoom.getRegion().intersects(shape);
        }
    private:
        RoomModel m_currentRoom;
        s3d::Optional<RoomModel> m_nextRoom;
    };
}