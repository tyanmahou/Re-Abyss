#pragma once
#include "../WorldObject.hpp"
#include "../Room.hpp"
#include "../DoorInfoModel.hpp"
namespace abyss
{
	class DoorModel : public WorldObject
	{
	private:
		s3d::Vec2 m_pos;
		s3d::Vec2 m_targetPos;
		s3d::Vec2 m_size;
		Room m_nextRoom;

	public:
		DoorModel(const DoorInfoModel& info, const Room& nextRoom);
		s3d::Shape getCollider() const override;

		const Room& getNextRoom() const;
		const s3d::Vec2& getPos() const;
		const s3d::Vec2& getTargetPos() const;
		s3d::Vec2 fixedVisiterPos(const s3d::Vec2& visitSize = { 22,80 }) const;
	};
}