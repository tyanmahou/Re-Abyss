#pragma once
#include <functional>

#include <Siv3D/Fwd.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/models/CameraModel.hpp>

namespace abyss
{
    class Camera
    {
	public:
		enum class Event
		{
			Nothing,
			OnCameraWorkStart,
			OnCameraWorkEnd,
			OnOutOfRoom,
			OnOutOfRoomDeath,
		};
	private:
		std::unique_ptr<CameraModel> m_camera;
		std::unique_ptr<ICameraWork> m_cameraWork;

		bool canNextRoom(const s3d::Vec2& pos) const;
		Event setCameraPos(const s3d::Vec2& pos);
		void adjustPlayerPos(PlayerActor& player);
	public:
		Camera();
		~Camera();

		Event update(PlayerActor& player);

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

		/// <summary>
		/// View作成
		/// </summary>
		/// <returns></returns>
		CameraView createView() const;

		/// <summary>
		/// スクリーンの範囲取得
		/// </summary>
		/// <returns></returns>
		s3d::RectF screenRegion() const;

		/// <summary>
		/// 現在の部屋取得
		/// </summary>
		/// <returns></returns>
		void setRoom(const RoomModel& room) const;

		/// <summary>
		/// 現在の部屋取得
		/// </summary>
		/// <returns></returns>
		const RoomModel& getCurrentRoom() const;

		template<class T>
		bool inRoom(const T& shape)const
		{
			return m_camera->inRoom(shape);
		}
    };
}
