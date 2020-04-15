#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Room/RoomModel.hpp>
#include <abyss/models/Actors/Door/DoorModel.hpp>

namespace abyss
{
	class DoorActor : public IActor
	{
	private:
		DoorModel m_door;
		RoomModel m_nextRoom;

	public:
		DoorActor(const DoorModel& door, const RoomModel& nextRoom);
		CShape getCollider() const override;

		const RoomModel& getNextRoom() const;
		const s3d::Vec2& getPos() const;
		const s3d::Vec2& getTargetPos() const;
		Forward getTargetForward() const;
		s3d::Vec2 fixedVisiterPos(const s3d::Vec2& visitSize = { 22,80 }) const;
		bool accept(const ActVisitor& visitor) override;
	};
}