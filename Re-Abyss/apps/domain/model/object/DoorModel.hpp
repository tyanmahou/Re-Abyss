#pragma once
#include "WorldObject.hpp"
#include "../RoomModel.hpp"

namespace abyss
{
	struct DoorEntity;

	class DoorModel : public WorldObject
	{
	private:
		s3d::Vec2 m_pos;
		s3d::Vec2 m_targetPos;
		s3d::Vec2 m_size;
		RoomModel m_nextRoom;

	public:
		DoorModel(const DoorEntity& entity, const RoomModel& nextRoom);
		CShape getCollider() const override;

		const RoomModel& getNextRoom() const;
		const s3d::Vec2& getPos() const;
		const s3d::Vec2& getTargetPos() const;
		s3d::Vec2 fixedVisiterPos(const s3d::Vec2& visitSize = { 22,80 }) const;
	};
}