#include "DoorActor.hpp"
#include <data/entity/DoorEntity.hpp>
#include <domain/visitor/ActVisitor.hpp>

#include <Siv3D.hpp>

namespace abyss
{
	DoorActor::DoorActor(const DoorEntity& entity, const RoomModel& nextRoom):
		m_pos(entity.pos),
		m_targetPos(entity.targetPos),
		m_size(entity.size),
		m_nextRoom(nextRoom)
	{
		this->tag = U"door";
	}
	CShape DoorActor::getCollider() const
	{
		return Circle(m_pos, 10);
	}
	const RoomModel& DoorActor::getNextRoom() const
	{
		return m_nextRoom;
	}
	const s3d::Vec2& DoorActor::getPos() const
	{
		return m_pos;
	}
	const Vec2& DoorActor::getTargetPos() const
	{
		return m_targetPos;
	}
	s3d::Vec2 DoorActor::fixedVisiterPos(const s3d::Vec2& visitSize) const
	{
		Vec2 ret = m_pos;
		ret.y += (m_size.y - visitSize.y) / 2.0;
		return ret;
	}
	void DoorActor::accept(const ActVisitor& visitor)
	{
		visitor.visit(*this);
	}
}