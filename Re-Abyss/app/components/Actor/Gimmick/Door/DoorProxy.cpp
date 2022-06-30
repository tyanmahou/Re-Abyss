#include <abyss/components/Actor/Gimmick/Door/DoorProxy.hpp>

namespace abyss::Actor::Gimmick::Door
{
	DoorProxy::DoorProxy(ActorObj* pActor, const DoorData& door, const Room::RoomData& nextRoom) :
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
	const Room::RoomData& DoorProxy::getNextRoom() const
	{
		return m_nextRoom;
	}
	void DoorProxy::setup([[maybe_unused]]Executer executer)
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
	DoorKind DoorProxy::getKind() const
	{
		return m_door.getKind();
	}
	bool DoorProxy::isSave() const
	{
		return m_door.isSave();
	}
	s3d::Vec2 DoorProxy::fixedVisiterPos(const s3d::Vec2& visitSize) const
	{
		return m_door.fixedVisiterPos(visitSize);
	}
	const DoorData& DoorProxy::getDoor() const
	{
		return m_door;
	}
}
