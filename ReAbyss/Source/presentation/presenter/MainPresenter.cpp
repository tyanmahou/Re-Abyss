#include "MainPresenter.hpp"

#include <domain/actor/PlayerActor.hpp>
#include <data/datastore/StageDataStore.hpp>

namespace abyss
{
	MainPresenter::MainPresenter() 
	{
		//auto onIntoDoor = [&](PlayerActor* player, const DoorActor& doorModel) {
		//	auto fadeInCallback = [player]() {
		//		player->setMotion(PlayerActor::Motion::Stay);
		//	};
		//	m_worldUseCase.reset();
		//	m_cameraUseCase.startDoorCameraWork(doorModel, player->getPos(), fadeInCallback);
		//};
		//m_worldUseCase.onIntoDoor().subscribe(onIntoDoor);

		//auto onOutSideRoom = [&](const Vec2& pos) {
		//	if (auto next = m_stageUseCase->findRoom(pos)) {
		//		m_worldUseCase.reset();
		//		m_cameraUseCase.startCameraWork(*next, pos);
		//	}
		//};
		//m_cameraUseCase.onOutSideRoom().subscribe(onOutSideRoom);
		//auto onNextRoom = [&](const RoomModel& room) {
		//	m_stageUseCase->initRoom(m_worldUseCase, room);
		//};
		//m_cameraUseCase.onNextRoom().subscribe(onNextRoom);

		//// init
		//if (auto room = m_stageUseCase->findRoom({ 480, 2000 })) {
		//	m_stageUseCase->init(m_worldUseCase, *room);
		//	m_cameraUseCase.setRoom(*room);
		//}
		//m_cameraUseCase.setPlayer(m_worldUseCase.getPlayer());
		//m_worldUseCase.setCamera(&m_cameraUseCase.getCamera());
	}
	void MainPresenter::update()
	{
		if (!m_cameraUseCase.isCameraWork()) {
			//m_worldUseCase.update();
		}
		m_cameraUseCase.update();
	}
	Observable<void(const std::shared_ptr<DoorCameraWork>&)>& MainPresenter::onStartDoorCameraWork()
	{
		return m_cameraUseCase.onStartDoorCameraWork();
	}
}


