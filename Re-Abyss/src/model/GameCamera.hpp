#pragma once
#include "Room.hpp"
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Graphics.hpp>
#include <Siv3D/Stopwatch.hpp>

#include <memory>

namespace abyss
{
	struct Transformer2D;
	class DoorModel;

	class ICameraWork;
	class GameCamera
	{
		static GameCamera* m_main;
	private:
		std::shared_ptr<ICameraWork> m_cameraWork;
		s3d::Vec2 m_pos;

		Room m_currentRoom;
		s3d::Optional<Room> m_nextRoom;

	public:
		GameCamera();

		void update(const s3d::Vec2 pos);
		void adjustPos(s3d::Vec2& pos);
		bool isOutOfRoomDeath(const s3d::Vec2& pos) const;

		void startCameraWork(const Room& nextRoom, const s3d::Vec2& playerPos, std::function<void()> callback = nullptr, double milliSec = 2000);
		void startDoorCameraWork(
			const DoorModel& door, 
			const s3d::Vec2& playerPos,
			std::function<void()> fadeInCallback = nullptr, 
			std::function<void()> fadeOutCallback = nullptr,
			double milliSec = 2000
		);

		void setRoom(const Room& room);

		void setPos(const s3d::Vec2 pos);
		const s3d::Vec2& getPos()const;

		s3d::RectF screenRegion() const;
		abyss::Transformer2D getTransformer() const;

		const Room& carentRoom() const;

		bool isCameraWork() const;

		void drawDeathLine() const;

		void drawCameraWork() const;
		static GameCamera*const Main();
	};
}