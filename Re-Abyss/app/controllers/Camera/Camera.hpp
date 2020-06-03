#pragma once
#include <functional>

#include <Siv3D/Fwd.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Camera/CameraModel.hpp>

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
		Manager* m_pManager;
		std::unique_ptr<CameraModel> m_camera;
		std::unique_ptr<ICameraWork> m_cameraWork;

		bool canNextRoom(const s3d::Vec2& pos) const;
		Event setCameraPos(const s3d::Vec2& pos);
		void adjustPlayerPos(Player::PlayerActor& player);
	public:
		Camera();
		~Camera();

		void setManager(Manager* pManager);

		Event update(Player::PlayerActor& player);

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
			const Door::DoorActor& door,
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

		/// <summary>
		/// 次の部屋取得
		/// </summary>
		/// <returns></returns>
		const s3d::Optional<RoomModel>& nextRoom()const;

		template<class T>
		bool inRoom(const T& shape)const
		{
			return m_camera->inRoom(shape);
		}

		template<class T>
		bool inScreen(const T& shape)const
		{
			return this->screenRegion().intersects(shape);
		}

		/// <summary>
		/// カメラ座標取得
		/// </summary>
		/// <returns></returns>
		const s3d::Vec2& getPos() const;
    };
}
