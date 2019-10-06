#pragma once
#include "RoomModel.hpp"
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Graphics.hpp>
#include <Siv3D/Stopwatch.hpp>

#include <memory>

namespace abyss
{
	class CameraModel
	{
	private:
		s3d::Vec2 m_pos;

		RoomModel m_currentRoom;
		s3d::Optional<RoomModel> m_nextRoom;

	public:
		CameraModel();

		bool isOutOfRoomDeath(const s3d::Vec2& pos) const;

		void setRoom(const RoomModel& room);
		const RoomModel& carentRoom() const;

		void setNextRoom(const s3d::Optional<RoomModel>& room);
		const s3d::Optional<RoomModel>& nextRoom() const;

		void setPos(const s3d::Vec2 pos);
		const s3d::Vec2& getPos()const;

		template<class T>
		bool inRoom(const T& shape)const
		{
			return m_currentRoom.getRegion().intersects(shape);
		}
	};
}