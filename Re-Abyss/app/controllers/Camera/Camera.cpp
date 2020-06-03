#include "Camera.hpp"

#include <abyss/models/Room/RoomModel.hpp>
#include <abyss/controllers/Stage/Stage.hpp>

#include <abyss/controllers/Actors/Player/PlayerActor.hpp>
#include <abyss/controllers/Actors/Gimmick/Door/DoorActor.hpp>
#include <abyss/views/Camera/CameraView.hpp>

#include "CameraWork/Door/DoorCameraWork.hpp"
#include "CameraWork/RoomMove/RoomMoveCameraWork.hpp"

namespace abyss
{
	bool Camera::canNextRoom(const s3d::Vec2& pos) const
	{
		return !this->isCameraWork() && !m_camera->currentRoom().getRegion().intersects(pos);
	}

	Camera::Event Camera::setCameraPos(const s3d::Vec2& pos)
	{
		Event event = Event::Nothing;

		Vec2 cameraPos = m_camera->getPos();
		if (this->isCameraWork()) {
			if (!m_cameraWork->isActive()) {
				m_cameraWork->start();
				m_cameraWork->onStart();

				event = Event::OnCameraWorkStart;
			}
			m_cameraWork->update();
			cameraPos = m_cameraWork->calcCameraPos();

			if (m_cameraWork->isEnd()) {
				m_cameraWork->onEnd();
				m_cameraWork = nullptr;
				m_camera->setNextRoom(s3d::none);

				event = Event::OnCameraWorkEnd;
			}
		} else {
			cameraPos = m_camera->currentRoom().cameraBorderAdjusted(pos);
		}
		m_camera->setPos(Math::Round(cameraPos));
		return event;
	}

	void Camera::adjustPlayerPos(Player::PlayerActor& player)
	{
		Vec2 pos = player.getPos();
		if (this->isCameraWork()) {
			if (auto playerPos = m_cameraWork->calcPlayerPos()) {
				pos = playerPos.value();
			}
		} else {
			pos = m_camera->currentRoom().borderAdjusted(pos);
		}
		player.setPos(pos);
	}

	Camera::Camera():
		m_camera(std::make_unique<CameraModel>())
	{}

	Camera::~Camera()
	{}

	void Camera::setManager(Manager * pManager)
	{
		m_pManager = pManager;
	}

	Camera::Event Camera::update(Player::PlayerActor& player)
	{
		const Vec2& pos =player.getPos();
		auto event = this->setCameraPos(pos);
		this->adjustPlayerPos(player);

		if (event != Event::Nothing) {
			return event;
		}
		if (m_camera->isOutOfRoomDeath(pos)) {
			return Event::OnOutOfRoomDeath;
		}
		if (this->canNextRoom(pos)) {
			return Event::OnOutOfRoom;
		}
		return event;
	}

	void Camera::startCameraWork(
		const RoomModel& nextRoom, 
		const s3d::Vec2& playerPos, 
		std::function<void()> callback,
		double milliSec
	) {
		assert(milliSec > 0);
		m_camera->setNextRoom(nextRoom);
		if (!callback) {
			callback = [this, nextRoom]() {
				m_camera->setRoom(nextRoom);
			};
		}
		m_cameraWork = RoomMoveCameraWork::Create(m_pManager, *m_camera, playerPos, callback, milliSec);
	}
	void Camera::startDoorCameraWork(
        const Door::DoorActor& door, 
        const s3d::Vec2& playerPos, 
        std::function<void()> fadeInCallback, 
        std::function<void()> fadeOutCallback,
        double milliSec
    ) {
		assert(milliSec > 0);

		const auto& nextRoom = door.getNextRoom();
		m_camera->setNextRoom(nextRoom);
		if (!fadeOutCallback) {
			fadeOutCallback = [this, nextRoom]() {
				this->setRoom(nextRoom);
			};
		}
		const auto& current = m_camera->currentRoom();
		Vec2 playerFrom = door.fixedVisiterPos();
		Vec2 playerTo = door.getTargetPos();
		Vec2 from = current.cameraBorderAdjusted(playerFrom);
		Vec2 to = nextRoom.cameraBorderAdjusted(playerTo);

		m_cameraWork = std::make_unique<DoorCameraWork>(
			m_pManager,
			std::make_pair(from, to),
			std::make_pair(playerFrom, playerTo),
			playerPos,
			fadeInCallback,
			fadeOutCallback,
			milliSec
		);
    }
    bool Camera::isCameraWork() const
    {
        return m_cameraWork != nullptr;
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
    const s3d::Optional<RoomModel>& Camera::nextRoom() const
    {
		return m_camera->nextRoom();
    }
    const s3d::Vec2& Camera::getPos() const
    {
		return m_camera->getPos();
    }
	CameraView Camera::createView() const
	{
		return CameraView(m_camera.get(), m_cameraWork.get());
	}
}