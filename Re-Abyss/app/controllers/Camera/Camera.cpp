#include "Camera.hpp"

#include <abyss/models/Room/RoomModel.hpp>
#include <abyss/models/Camera/QuakeModel.hpp>

#include <abyss/controllers/Actors/Player/PlayerActor.hpp>
#include <abyss/controllers/Camera/CameraWork/base/ICameraWork.hpp>
#include <abyss/views/Camera/CameraView.hpp>

namespace abyss
{
	Camera::Camera():
		m_camera(std::make_unique<CameraModel>())
	{}

	Camera::~Camera()
	{}

	void Camera::setManager(Manager * pManager)
	{
		m_pManager = pManager;
	}

	void Camera::update()
	{
		auto player = m_pManager->getModule<Player::PlayerActor>();
		const Vec2& playerPos = player->getPos();

		// カメラ座標調整
		{
			Vec2 cameraPos = m_camera->getPos();
			if (this->isCameraWork()) {
				// カメラワーク中
				if (!m_cameraWork->isActive()) {
					m_cameraWork->start();
					m_cameraWork->onStart();
				}
				m_cameraWork->update();
				cameraPos = m_cameraWork->calcCameraPos();

				if (m_cameraWork->isEnd()) {
					m_cameraWork->onEnd();
					m_cameraWork = nullptr;
				}
			} else {
				cameraPos = m_camera
					->currentRoom()
					.cameraBorderAdjusted(playerPos);
			}
			// 地震適用
			if (this->isQuake()) {
				cameraPos = m_quake->apply(cameraPos);

				if (m_quake->IsEnd()) {
					m_quake = nullptr;
				}
			}
			m_camera->setPos(Math::Round(cameraPos));
		}
	}

	bool Camera::isCameraWork() const
    {
        return m_cameraWork != nullptr;
    }
	void Camera::startQuake(double maxOffset, double timeSec)
	{
		m_quake = std::make_unique<QuakeModel>(m_pManager, maxOffset, timeSec);
	}
	void Camera::stopQuake()
	{
		m_quake = nullptr;
	}
	bool Camera::isQuake() const
	{
		return m_quake != nullptr;
	}
    s3d::RectF Camera::screenRegion() const
    {
		return this->createView().screenRegion();
    }
	void Camera::setRoom(const RoomModel& room) const
	{
		m_camera->setRoom(room);
	}
	const RoomModel& Camera::getCurrentRoom() const
	{
		return m_camera->currentRoom();
	}
	void Camera::setNextRoom(const s3d::Optional<RoomModel>& nextRoom) const
	{
		m_camera->setNextRoom(nextRoom);
	}
    const s3d::Optional<RoomModel>& Camera::nextRoom() const
    {
		return m_camera->nextRoom();
    }
	bool Camera::applyNextRoom() const
	{
		if (auto nextRoom = m_camera->nextRoom()) {
			m_camera->setRoom(*nextRoom);
			m_camera->setNextRoom(s3d::none);
			return true;
		}
		return false;
	}
	void Camera::setPos(const s3d::Vec2& cameraPos) const
	{
		m_camera->setPos(Math::Round(cameraPos));
	}
	const s3d::Vec2& Camera::getPos() const
    {
		return m_camera->getPos();
    }
	CameraView Camera::createView() const
	{
		return CameraView(m_camera.get());
	}

	bool Camera::canNextRoom(const s3d::Vec2& pos) const
	{
		return !this->isCameraWork() && !m_camera->currentRoom().getRegion().intersects(pos);
	}
}