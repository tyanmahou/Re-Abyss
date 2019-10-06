#include "MainPresenter.hpp"

#include <domain/actor/PlayerActor.hpp>

#include <presentation/view/main/MainView.hpp>
#include <presentation/view/main/object/PlayerView.hpp>
#include <presentation/view/main/object/SlimeView.hpp>

#include <data/datastore/StageDataStore.hpp>

namespace abyss
{
	MainPresenter::MainPresenter(std::shared_ptr<IMainView> view) :
		m_view(view)
	{
		// •`‰æî•ñ‚ðview‚É“n‚·
		auto onLoadStageFile = [this](IStageDataStore* dataStore) {
			// ”wŒi“o˜^
			for (const auto& bg : dataStore->getBackGroundEntity()) {
				m_view->addBackGroundView(BackGroundVM(bg));
			}
		};

		auto onCreateObject = [this](const auto& model) {
			if (auto view = m_view->getFactory().createFromModel(model)) {
				m_view->addWorldObjectView(std::move(view));
			}
		};
		m_worldUseCase.subsucrimeCreateObject(std::move(onCreateObject));

		auto onIntoDoor = [&](PlayerActor* player, const DoorActor& doorModel) {
			auto fadeInCallback = [player]() {
				player->setMotion(PlayerActor::Motion::Stay);
			};
			m_worldUseCase.reset();
			m_cameraUseCase.startDoorCameraWork(doorModel, player->getPos(), fadeInCallback);
		};
		m_worldUseCase.onIntoDoor().subscribe(onIntoDoor);

		auto onOutSideRoom = [&](const Vec2& pos) {
			if (auto next = m_stageUseCase->findRoom(pos)) {
				m_worldUseCase.reset();
				m_cameraUseCase.startCameraWork(*next, pos);
			}
		};
		m_cameraUseCase.onOutSideRoom().subscribe(onOutSideRoom);
		auto onNextRoom = [&](const RoomModel& room) {
			m_stageUseCase->initRoom(m_worldUseCase, room);
		};
		m_cameraUseCase.onNextRoom().subscribe(onNextRoom);
		auto onStartDoorCameraWork = [&](const std::shared_ptr<DoorCameraWork>& work) {
			auto view = m_view->getFactory().createFromCameraWork(work);
			m_view->setCameraWorkView(std::move(view));
		};
		m_cameraUseCase.onStartDoorCameraWork().subscribe(onStartDoorCameraWork);
		// init
		if (auto room = m_stageUseCase->findRoom({ 480, 2000 })) {
			m_stageUseCase->init(m_worldUseCase, *room);
			m_cameraUseCase.setRoom(*room);
		}
		m_cameraUseCase.setPlayer(m_worldUseCase.getPlayer());
		m_worldUseCase.setCamera(&m_cameraUseCase.getCamera());

		m_view->createCameraView(m_cameraUseCase.getCamera());
	}
	void MainPresenter::update()
	{
		if (!m_cameraUseCase.isCameraWork()) {
			m_worldUseCase.update();
		}
		m_cameraUseCase.update();
	}
}


