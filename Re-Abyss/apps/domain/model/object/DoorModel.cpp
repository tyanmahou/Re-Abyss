#include "DoorModel.hpp"
#include <data/entity/DoorEntity.hpp>
#include <Siv3D.hpp>

namespace abyss
{
	DoorModel::DoorModel(const DoorEntity& entity, const RoomModel& nextRoom):
		m_pos(entity.pos),
		m_targetPos(entity.targetPos),
		m_size(entity.size),
		m_nextRoom(nextRoom)
	{
		this->tag = L"door";
	}
	CShape DoorModel::getCollider() const
	{
		return Circle(m_pos, 10);
	}
	const RoomModel& DoorModel::getNextRoom() const
	{
		return m_nextRoom;
	}
	const s3d::Vec2& DoorModel::getPos() const
	{
		return m_pos;
	}
	const Vec2& DoorModel::getTargetPos() const
	{
		return m_targetPos;
	}
	s3d::Vec2 DoorModel::fixedVisiterPos(const s3d::Vec2& visitSize) const
	{
		Vec2 ret = m_pos;
		ret.y += (m_size.y - visitSize.y) / 2.0;
		return ret;
	}
}