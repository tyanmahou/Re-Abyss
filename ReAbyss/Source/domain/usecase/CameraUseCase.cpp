#include "CameraUseCase.hpp"
#include <domain/model/CameraWork.hpp>
#include <domain/actor/PlayerActor.hpp>
#include <domain/actor/DoorActor.hpp>
#include <domain/model/RoomModel.hpp>
namespace abyss
{
	bool CameraUseCase::canNextRoom(const s3d::Vec2& pos) const
	{
		return !this->isCameraWork() && !m_camera.carentRoom().getRegion().intersects(pos);
	}
	void CameraUseCase::setCameraPos(const Vec2& pos)
	{
		Vec2 cameraPos = m_camera.getPos();
		if (this->isCameraWork()) {
			m_cameraWork->update();
			cameraPos = m_cameraWork->calcCameraPos();

			if (m_cameraWork->isEnd()) {
				m_cameraWork->onEnd();
				m_cameraWork = nullptr;
				m_camera.setNextRoom(s3d::none);
			}
		}
		else {
			cameraPos = m_camera.carentRoom().cameraBorderAdjusted(pos);
		}
		m_camera.setPos(Math::Ceil(cameraPos));
	}
	void CameraUseCase::adjustPlayerPos()
	{
		Vec2 pos = m_pPlayer->getPos();
		if (this->isCameraWork()) {
			if (auto playerPos = m_cameraWork->calcPlayerPos()) {
				pos = playerPos.value();
			}
		}
		else {
			pos = m_camera.carentRoom().borderAdjusted(pos);
		}
		m_pPlayer->setPos(pos);
	}
	void CameraUseCase::setPlayer(PlayerActor* pPlayer)
	{
		m_pPlayer = pPlayer;
	}
	void CameraUseCase::update()
	{
		const Vec2& pos = m_pPlayer->getPos();
		this->setCameraPos(pos);
		this->adjustPlayerPos();

		if (m_camera.isOutOfRoomDeath(pos)) {
			return;
		}
		if (this->canNextRoom(pos)) {
			this->onOutSideRoom().notify(pos);
		}
	}
	void CameraUseCase::startCameraWork(
		const RoomModel& nextRoom,
		const s3d::Vec2& playerPos,
		std::function<void()> callback,
		double milliSec
	){
		assert(milliSec > 0);
		m_camera.setNextRoom(nextRoom);
		if (!callback) {
			callback = [this, nextRoom]() {
				this->setRoom(nextRoom);
			};
		}
		m_cameraWork = RoomMoveCameraWork::Create(m_camera, playerPos, callback, milliSec);
	}
	void CameraUseCase::startDoorCameraWork(
		const DoorActor& door,
		const s3d::Vec2& playerPos, 
		std::function<void()> fadeInCallback, 
		std::function<void()> fadeOutCallback,
		double milliSec
	) {
		const auto& nextRoom = door.getNextRoom();
		m_camera.setNextRoom(nextRoom);
		if (!fadeOutCallback) {
			fadeOutCallback = [this, nextRoom]() {
				this->setRoom(nextRoom);
			};
		}
		const auto& current = m_camera.carentRoom();
		Vec2 playerFrom = door.fixedVisiterPos();
		Vec2 playerTo = door.getTargetPos();
		Vec2 from = current.cameraBorderAdjusted(playerFrom);
		Vec2 to = nextRoom.cameraBorderAdjusted(playerTo);

		auto work = std::make_shared<DoorCameraWork>(
			std::make_pair(from, to),
			std::make_pair(playerFrom, playerTo),
			playerPos,
			fadeInCallback,
			fadeOutCallback,
			milliSec
		);
		m_cameraWork = work;
		this->onStartDoorCameraWork().notify(work);
	}
	void CameraUseCase::setRoom(const RoomModel& room)
	{
		m_camera.setRoom(room);
		this->onNextRoom().notify(room);
	}
	bool CameraUseCase::isCameraWork() const
	{
		return m_cameraWork != nullptr;
	}
	const CameraModel& CameraUseCase::getCamera() const
	{
		return m_camera;
	}
}
