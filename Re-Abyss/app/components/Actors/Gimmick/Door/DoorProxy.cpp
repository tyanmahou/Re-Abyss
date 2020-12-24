#include "DoorProxy.hpp"

namespace abyss::Actor::Gimmick::Door
{
	DoorProxy::DoorProxy(IActor* pActor, const DoorModel& door, const RoomModel& nextRoom) :
		m_pActor(pActor),
		m_door(door),
		m_nextRoom(nextRoom)
	{
	}
	CShape DoorProxy::getCollider() const
	{
		return Circle(this->getPos(), 10);
	}
	s3d::int32 DoorProxy::getStartId() const
	{
		return m_door.getStartId();
	}
	const RoomModel& DoorProxy::getNextRoom() const
	{
		return m_nextRoom;
	}
	void DoorProxy::setup([[maybe_unused]]Depends depends)
	{}
	void DoorProxy::onStart()
	{}

	const s3d::Vec2& DoorProxy::getPos() const
	{
		return m_door.getPos();
	}
	const Vec2& DoorProxy::getTargetPos() const
	{
		return m_door.getTargetPos();
	}
	Forward DoorProxy::getTargetForward() const
	{
		return m_door.getTargetForward();
	}
	bool DoorProxy::isSave() const
	{
		return m_door.isSave();
	}
	s3d::Vec2 DoorProxy::fixedVisiterPos(const s3d::Vec2& visitSize) const
	{
		return m_door.fixedVisiterPos(visitSize);
	}
	const DoorModel& DoorProxy::getDoor() const
	{
		return m_door;
	}
}
