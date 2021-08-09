#include "RoomManager.hpp"

namespace abyss::Room
{
	RoomManager::RoomManager()
	{}
	bool RoomManager::isOutOfRoomDeath(const s3d::Vec2& pos, double margin) const
    {
		if (!m_currentRoom.passable(Forward::Down) && pos.y > m_currentRoom.borders().down + margin) {
			return true;
		}
		return false;
    }
}
