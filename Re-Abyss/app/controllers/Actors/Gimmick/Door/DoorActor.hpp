#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Room/RoomModel.hpp>
#include <abyss/models/Actors/Gimmick/Door/DoorModel.hpp>

namespace abyss::Actor::Gimmick::Door
{
	class DoorActor : public IActor
	{
	private:
		DoorModel m_door;
		RoomModel m_nextRoom;

	public:
		DoorActor(const DoorModel& door, const RoomModel& nextRoom);
		CShape getCollider() const;

		s3d::int32 getStartId()const;
		const RoomModel& getNextRoom() const;
		const s3d::Vec2& getPos() const;
		const s3d::Vec2& getTargetPos() const;
		Forward getTargetForward() const;
		bool isSave()const;
		s3d::Vec2 fixedVisiterPos(const s3d::Vec2& visitSize = { 22,80 }) const;
	};
}