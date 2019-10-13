#pragma once
#include <domain/model/CameraModel.hpp>
#include "CameraObservable.hpp"

namespace abyss
{
	class PlayerActor;
	class DoorActor;
	class ICameraWork;

	class ICameraUseCase : public CamraObservable
	{

	};

	class CameraUseCase : public ICameraUseCase
	{
		CameraModel m_camera;
		std::shared_ptr<ICameraWork> m_cameraWork;

		std::shared_ptr<PlayerActor> m_pPlayer;
		const DoorActor* m_pIntoDoor = nullptr;

		bool canNextRoom(const s3d::Vec2& pos) const;

		void setCameraPos(const s3d::Vec2& pos);
		void adjustPlayerPos();
	public:
		void initPlayer(const std::shared_ptr<PlayerActor>& pPlayer);
		void update();

		void startCameraWork(
			const RoomModel& nextRoom, 
			const s3d::Vec2& playerPos, 
			std::function<void()> callback = nullptr, 
			double milliSec = 2000
		);

		void startDoorCameraWork(
			const DoorActor& door,
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