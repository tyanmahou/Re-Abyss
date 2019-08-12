#pragma once
#include "Room.hpp"
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Graphics.hpp>
#include <Siv3D/Stopwatch.hpp>

namespace abyss
{
	struct Transformer2D;

	class GameCamera
	{
		static GameCamera* m_main;
	private:
		s3d::Vec2 m_pos;
		Room m_currentRoom;
		s3d::Vec2 m_movePos;
		s3d::Optional<std::pair<s3d::Vec2, s3d::Vec2>> m_playerMovePos;
		s3d::Stopwatch m_animation;
		std::function<void()> m_callback;
		double m_animeMilliSec = 0;

		double elapsed() const;
	public:
		GameCamera();

		void update(const s3d::Vec2 pos);
		void adjustPos(s3d::Vec2& pos);

		GameCamera& startCameraWork(const s3d::Vec2& pos, std::function<void()> callback = nullptr, double milliSec = 2000);
		GameCamera& startCameraWork(const Room& nextRoom, std::function<void()> callback = nullptr, double milliSec = 2000);
		bool withPlayerPos(const s3d::Vec2& currentPos);
		void setRoom(const Room& room);
		void setPos(const s3d::Vec2 pos);
		const s3d::Vec2& getPos()const;
		s3d::Rect screenRegion() const;
		abyss::Transformer2D getTransformer() const;
		const Room& carentRoom() const;

		bool isCameraWork() const;

		static GameCamera*const Main();
	};
}