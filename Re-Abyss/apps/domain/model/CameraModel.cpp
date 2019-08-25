#include "CameraModel.hpp"

using namespace s3d;

namespace abyss
{

	CameraModel::CameraModel()
	{}

	bool CameraModel::isOutOfRoomDeath(const s3d::Vec2& pos) const
	{
		if (!m_currentRoom.passable(Forward::Down) && pos.y > m_currentRoom.borders().down) {
			return true;
		}
		return false;
	}

	void CameraModel::setRoom(const RoomModel& room)
	{
		m_currentRoom = room;
	}
	void CameraModel::setPos(const s3d::Vec2 pos)
	{
		m_pos = m_currentRoom.cameraBorderAdjusted(pos);
	}
	const s3d::Vec2& CameraModel::getPos() const
	{
		return m_pos;
	}
	const RoomModel & CameraModel::carentRoom() const
	{
		return m_currentRoom;
	}
	void CameraModel::setNextRoom(const s3d::Optional<RoomModel>& room)
	{
		m_nextRoom = room;
	}
	const s3d::Optional<RoomModel>& CameraModel::nextRoom() const
	{
		return m_nextRoom;
	}
}