#pragma once
#include <functional>

#include <Siv3D/Fwd.hpp>

#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class Camera
    {
		std::shared_ptr<CameraModel> m_camera;
		std::unique_ptr<ICameraWork> m_cameraWork;

		std::shared_ptr<PlayerActor> m_pPlayer;

		bool canNextRoom(const s3d::Vec2& pos) const;
		void setCameraPos(const s3d::Vec2& pos);
		void adjustPlayerPos();
	public:

		void update();

		/// <summary>
		/// 部屋移動のカメラワーク開始
		/// </summary>
		/// <param name="nextRoom"></param>
		/// <param name="playerPos"></param>
		/// <param name="callback"></param>
		/// <param name="milliSec"></param>
		void startCameraWork(
			const RoomModel& nextRoom,
			const s3d::Vec2& playerPos,
			std::function<void()> callback = nullptr,
			double milliSec = 2000
		);

		/// <summary>
		/// ドア入りカメラワーク
		/// </summary>
		/// <param name="door"></param>
		/// <param name="playerPos"></param>
		/// <param name="fadeInCallback"></param>
		/// <param name="fadeOutCallback"></param>
		/// <param name="milliSec"></param>
		void startDoorCameraWork(
			const DoorActor& door,
			const s3d::Vec2& playerPos,
			std::function<void()> fadeInCallback = nullptr,
			std::function<void()> fadeOutCallback = nullptr,
			double milliSec = 2000
		);

		bool isCameraWork() const;

		s3d::RectF screenRegion() const;
    };
}
