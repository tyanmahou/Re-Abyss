#include "MainPresenter.hpp"

#include <domain/model/object/PlayerModel.hpp>
#include <domain/model/object/PlayerShotModel.hpp>
#include <domain/model/object/SlimeModel.hpp>
#include <domain/model/object/DoorModel.hpp>
#include <presentation/view/main/MainView.hpp>
#include <presentation/view/main/object/PlayerView.hpp>

#include <data/datastore/StageDataStore.hpp>

namespace
{
	using namespace abyss;

	template<class Type>
	auto NotifyCreateObject(const std::shared_ptr<IMainView>& view, const std::shared_ptr<Type>& object)
		->std::enable_if_t<std::is_base_of<WorldObject, Type>::value>
	{
		if (auto objView = view->getFactory()->createViewFromModel(object)) {
			view->addWorldObjectView(std::move(objView));
		}
	}
}
namespace abyss
{
	MainPresenter::MainPresenter(std::shared_ptr<IMainView> view) :
		m_view(view)
	{
		// •`‰æî•ñ‚ðview‚É“n‚·
		auto onLoadStageFile = [this](IStageDataStore * dataStore) {
			// ”wŒi“o˜^
			for (const auto& bg : dataStore->getBackGroundEntity()) {
				m_view->addBackGroundView(BackGroundVM(bg));
			}
			// ƒ}ƒbƒv•`‰æ“o˜^
			for (const auto& layer : dataStore->getLayerViewEntity()) {
				m_view->addLayerView(layer.layerName, layer.drawCallback);
			}
		};
		m_stageUseCase.onLoadStageFile().subscribe(onLoadStageFile);

		m_worldUseCase.subscribe([this](const std::shared_ptr<PlayerModel> & model) {
			::NotifyCreateObject<PlayerModel>(this->m_view, model);
			});
		m_worldUseCase.subscribe([this](const std::shared_ptr<PlayerShotModel> & model) {
			::NotifyCreateObject<PlayerShotModel>(this->m_view, model);
			});
		m_worldUseCase.subscribe([this](const std::shared_ptr<SlimeModel> & model) {
			::NotifyCreateObject<SlimeModel>(this->m_view, model);
		});

		auto onIntoDoor = [&](PlayerModel * player, const DoorModel& doorModel) {
			auto fadeInCallback = [player]() {
				player->setMotion(PlayerModel::Motion::Stay);
			};
			m_worldUseCase.reset();
			m_cameraUseCase.startDoorCameraWork(doorModel, player->getPos(), fadeInCallback);
		};
		m_worldUseCase.onIntoDoor().subscribe(onIntoDoor);

		auto onOutSideRoom = [&](const Vec2 & pos) {
			if (auto next = m_stageUseCase.findRoom(pos)) {
				m_worldUseCase.reset();
				m_cameraUseCase.startCameraWork(*next, pos);
			}
		};
		m_cameraUseCase.onOutSideRoom().subscribe(onOutSideRoom);
		auto onNextRoom = [&](const RoomModel & room) {
			m_stageUseCase.initRoom(m_worldUseCase, room);
		};
		m_cameraUseCase.onNextRoom().subscribe(onNextRoom);
		auto onStartDoorCameraWork = [&](const std::shared_ptr<DoorCameraWork> & work) {
			auto view = m_view->getFactory()->createViewFromModel(work);
			m_view->setCameraWorkView(std::move(view));
		};
		m_cameraUseCase.onStartDoorCameraWork().subscribe(onStartDoorCameraWork);
		// init
		m_stageUseCase.load(L"work/stage0/stage0.tmx");
		if (auto room = m_stageUseCase.findRoom({ 480, 2000 })) {
			m_stageUseCase.init(m_worldUseCase, *room);
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


