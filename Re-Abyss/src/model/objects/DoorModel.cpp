#include "DoorModel.hpp"
#include <Siv3D.hpp>

namespace abyss
{
	DoorModel::DoorModel(const DoorInfoModel& info, const Room& nextRoom):
		m_pos(info.pos),
		m_targetPos(info.targetPos),
		m_size(info.size),
		m_nextRoom(nextRoom)
	{
		this->tag = L"door";
	}
	s3d::Shape DoorModel::getCollider() const
	{
		return static_cast<s3d::Shape>(Circle(m_pos, 10));
	}
	const Room& DoorModel::getNextRoom() const
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