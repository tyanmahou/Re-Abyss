#include "CameraUseCase.hpp"
#include <domain/model/CameraWork.hpp>
#include <domain/model/object/PlayerModel.hpp>

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
			cameraPos = pos;
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
	void CameraUseCase::setPlayer(PlayerModel* pPlayer)
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
			this->onNextRoom().notify(this);
		}
	}
	void CameraUseCase::startCameraWork(const RoomModel& nextRoom, const s3d::Vec2& playerPos, std::function<void()> callback, double milliSec)
	{
		m_camera.setRoom(nextRoom);
	}
	void CameraUseCase::setRoom(const RoomModel& room)
	{
		m_camera.setRoom(room);
	}
	bool CameraUseCase::isCameraWork() const
	{
		return m_cameraWork != nullptr;
	}
	const CameraModel& CameraUseCase::getCamera() const
	{
		return m_camera;
	}
	//void GameCamera::startCameraWork(const Room& nextRoom, const s3d::Vec2& playerPos, std::function<void()> callback, double milliSec)
	//{
	//	assert(milliSec > 0);

	//	m_nextRoom = nextRoom;

	//	Vec2 from = m_currentRoom.cameraBorderAdjusted(m_pos);
	//	Vec2 to = nextRoom.cameraBorderAdjusted(m_pos);
	//	if (!callback) {
	//		callback = [this, nextRoom]() {
	//			this->setRoom(nextRoom);
	//		};
	//	}

	//	// プレイヤーの位置計算
	//	Vec2 target = playerPos;
	//	Vec2 v = to - from;

	//	bool isHorizontal = Math::Abs(v.x) > Math::Abs(v.y);
	//	auto border = m_currentRoom.borders();
	//	if (isHorizontal) {
	//		if (v.x > 0) {
	//			target.x = border.right + 40;
	//		}
	//		else {
	//			target.x = border.left - 40;
	//		}
	//	}
	//	else {
	//		if (v.y > 0) {
	//			target.y = border.down + 40;
	//		}
	//		else {
	//			target.y = border.up - 40;
	//		}
	//	}
	//	m_cameraWork = std::make_shared<RoomMoveCameraWork>(
	//		std::make_pair(from, to),
	//		std::make_pair(playerPos, target),
	//		callback,
	//		milliSec
	//		);
	//}

	//void GameCamera::startDoorCameraWork(const DoorModel& door, const s3d::Vec2& playerPos, std::function<void()> fadeInCallback, std::function<void()> fadeOutCallback, double milliSec)
	//{
	//	m_nextRoom = door.getNextRoom();
	//	Vec2 playerFrom = door.fixedVisiterPos();
	//	Vec2 playerTo = door.getTargetPos();
	//	Vec2 from = m_currentRoom.cameraBorderAdjusted(playerFrom);
	//	Vec2 to = m_nextRoom->cameraBorderAdjusted(playerTo);

	//	if (!fadeOutCallback) {
	//		fadeOutCallback = [this]() {
	//			this->setRoom(*m_nextRoom);
	//		};
	//	}
	//	m_cameraWork = std::make_shared<DoorCameraWork>(
	//		std::make_pair(from, to),
	//		std::make_pair(playerFrom, playerTo),
	//		playerPos,
	//		fadeInCallback,
	//		fadeOutCallback,
	//		milliSec
	//		);
	//}

}
