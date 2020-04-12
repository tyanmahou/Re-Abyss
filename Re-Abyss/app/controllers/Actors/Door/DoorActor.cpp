#include "DoorActor.hpp"
#include <abyss/commons/LayerGroup.hpp>
#include <Siv3D.hpp>

namespace abyss
{
	DoorActor::DoorActor(const DoorModel& door, const RoomModel& nextRoom):
		m_door(door),
		m_nextRoom(nextRoom)
	{
		this->layer = LayerGroup::Gimmick;
		this->tag = U"door";
	}
	CShape DoorActor::getCollider() const
	{
		return Circle(this->getPos(), 10);
	}
	const RoomModel& DoorActor::getNextRoom() const
	{
		return m_nextRoom;
	}
	const s3d::Vec2& DoorActor::getPos() const
	{
		return m_door.getPos();
	}
	const Vec2& DoorActor::getTargetPos() const
	{
		return m_door.getTargetPos();
	}
	s3d::Vec2 DoorActor::fixedVisiterPos(const s3d::Vec2& visitSize) const
	{
		return m_door.fixedVisiterPos(visitSize);
	}
	bool DoorActor::accept(const ActVisitor& visitor)
	{
		return visitor.visit(*this);
	}
}