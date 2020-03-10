#include "CameraController.hpp"

#include <abyss/models/Camera/CameraModel.hpp>
#include <abyss/models/Camera/CameraWork.hpp>
#include <abyss/models/Room/RoomModel.hpp>

#include <abyss/models/actors/Player/PlayerActor.hpp>
#include <abyss/models/actors/Door/DoorActor.hpp>


namespace abyss
{
	bool CameraController::canNextRoom(const s3d::Vec2& pos) const
	{
		return !this->isCameraWork() && !m_camera->currentRoom().getRegion().intersects(pos);
	}

	void CameraController::setCameraPos(const s3d::Vec2& pos)
	{
		Vec2 cameraPos = m_camera->getPos();
		if (this->isCameraWork()) {
			m_cameraWork->update();
			cameraPos = m_cameraWork->calcCameraPos();

			if (m_cameraWork->isEnd()) {
				m_cameraWork->onEnd();
				m_cameraWork = nullptr;
				m_camera->setNextRoom(s3d::none);
			}
		} else {
			cameraPos = m_camera->currentRoom().cameraBorderAdjusted(pos);
		}
		m_camera->setPos(Math::Ceil(cameraPos));
	}

	void CameraController::adjustPlayerPos()
	{
		Vec2 pos = m_pPlayer->getPos();
		if (this->isCameraWork()) {
			if (auto playerPos = m_cameraWork->calcPlayerPos()) {
				pos = playerPos.value();
			}
		} else {
			pos = m_camera->currentRoom().borderAdjusted(pos);
		}
		m_pPlayer->setPos(pos);
	}

	void CameraController::update()
	{
		const Vec2& pos = m_pPlayer->getPos();
		this->setCameraPos(pos);
		this->adjustPlayerPos();

		if (m_camera->isOutOfRoomDeath(pos)) {
			return;
		}
		if (this->canNextRoom(pos)) {
			// this->onOutSideRoom().notify(pos);
		}
	}

	void CameraController::startCameraWork(
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
		m_cameraWork = RoomMoveCameraWork::Create(*m_camera, playerPos, callback, milliSec);
	}
	void CameraController::startDoorCameraWork(
        const DoorActor& door, 
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
				//this->setRoom(nextRoom);
			};
		}
		const auto& current = m_camera->currentRoom();
		Vec2 playerFrom = door.fixedVisiterPos();
		Vec2 playerTo = door.getTargetPos();
		Vec2 from = current.cameraBorderAdjusted(playerFrom);
		Vec2 to = nextRoom.cameraBorderAdjusted(playerTo);

		m_cameraWork = std::make_unique<DoorCameraWork>(
			std::make_pair(from, to),
			std::make_pair(playerFrom, playerTo),
			playerPos,
			fadeInCallback,
			fadeOutCallback,
			milliSec
		);
    }
    bool CameraController::isCameraWork() const
    {
        return m_cameraWork != nullptr;
    }
}