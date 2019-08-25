#pragma once
#include <domain/model/CameraModel.hpp>
#include "CameraObservable.hpp"
namespace abyss
{
	class PlayerModel;
	class DoorModel;
	class ICameraWork;

	class CameraUseCase : public CamraObservable
	{
		CameraModel m_camera;
		PlayerModel* m_pPlayer;
		std::shared_ptr<ICameraWork> m_cameraWork;

		bool canNextRoom(const s3d::Vec2& pos) const;

		void setCameraPos(const s3d::Vec2& pos);
		void adjustPlayerPos();
	public:
		void setPlayer(PlayerModel* pPlayer);
		void update();

		void startCameraWork(const RoomModel& nextRoom, const s3d::Vec2& playerPos, std::function<void()> callback = nullptr, double milliSec = 2000);
		void startDoorCameraWork(
			const DoorModel& door,
			const s3d::Vec2& playerPos,
			std::function<void()> fadeInCallback = nullptr,
			std::function<void()> fadeOutCallback = nullptr,
			double milliSec = 2000
		);

		void setRoom(const RoomModel& room);
		bool isCameraWork()const;

		const CameraModel& getCamera() const;
	};
}