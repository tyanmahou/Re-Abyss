#include "DoorActor.hpp"
#include <abyss/models/Collision/LayerGroup.hpp>
#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>

#include <Siv3D.hpp>

namespace abyss::Door
{
	DoorActor::DoorActor(const DoorModel& door, const RoomModel& nextRoom):
		m_door(door),
		m_nextRoom(nextRoom)
	{
		auto col = this->attach<CustomColliderModel>(this);
		col->setLayer(LayerGroup::Gimmick);

		col->setColFunc([this] {return this->getCollider(); });
	}
	CShape DoorActor::getCollider() const
	{
		return Circle(this->getPos(), 10);
	}
	s3d::int32 DoorActor::getStartId() const
	{
		return m_door.getStartId();
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
	Forward DoorActor::getTargetForward() const
	{
		return m_door.getTargetForward();
	}
	bool DoorActor::isSave() const
	{
		return m_door.isSave();
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