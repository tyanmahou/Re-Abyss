#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Room/RoomModel.hpp>

namespace abyss
{
	class DoorActor : public IActor
	{
	private:
		s3d::Vec2 m_pos;
		s3d::Vec2 m_targetPos;
		s3d::Vec2 m_size;
		RoomModel m_nextRoom;

	public:
		DoorActor(const DoorEntity& entity, const RoomModel& nextRoom);
		CShape getCollider() const override;

		const RoomModel& getNextRoom() const;
		const s3d::Vec2& getPos() const;
		const s3d::Vec2& getTargetPos() const;
		s3d::Vec2 fixedVisiterPos(const s3d::Vec2& visitSize = { 22,80 }) const;
		bool accept(const ActVisitor& visitor) override;
	};
}