#include "CameraModel.hpp"
#include <abyss/commons/Constants.hpp>
using namespace s3d;

namespace abyss
{

	CameraModel::CameraModel():
		m_pos(Constants::GameScreen.center()),
		m_targetPos(Constants::GameScreen.center()),
		m_currentRoom{Constants::GameScreen, 0}
	{}

	bool CameraModel::isOutOfRoomDeath(const s3d::Vec2& pos, double margin) const
	{
		if (!m_currentRoom.passable(Forward::Down) && pos.y > m_currentRoom.borders().down + margin) {
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
		m_pos = pos;
	}
	const s3d::Vec2& CameraModel::getPos() const
	{
		return m_pos;
	}
	void CameraModel::setTargetPos(const s3d::Vec2 pos)
	{
		m_targetPos = pos;
	}
	const s3d::Vec2& CameraModel::getTargetPos() const
	{
		return m_targetPos;
	}
	const RoomModel & CameraModel::currentRoom() const
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