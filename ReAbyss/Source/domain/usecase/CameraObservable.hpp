#pragma once

#include <application/util/Observable.hpp>
#include <memory>
namespace abyss
{
	class CameraUseCase;
	class RoomModel;
	class DoorCameraWork;

	class CamraObservable
	{
		Observable<void(const RoomModel&)> m_onNextRoom;
		Observable<void(const s3d::Vec2&)> m_onOutSideRoom;

		Observable<void(const std::shared_ptr<DoorCameraWork>&)> m_onStartDoorCameraWork;
	public:
		inline Observable<void(const RoomModel&)>& onNextRoom()
		{
			return m_onNextRoom;
		}
		inline Observable<void(const s3d::Vec2&)>& onOutSideRoom()
		{
			return m_onOutSideRoom;
		}
		inline Observable<void(const std::shared_ptr<DoorCameraWork>&)>& onStartDoorCameraWork()
		{
			return m_onStartDoorCameraWork;
		}
	};
}
