#include "MainPresenter.hpp"

#include "../../domain/model/object/PlayerModel.hpp"
#include "../../domain/model/object/PlayerShotModel.hpp"
#include "../view/main/MainView.hpp"
#include "../view/main/object/PlayerView.hpp"

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
		m_view(view),
		m_stageUseCase(L"work/stage0/stage0.tmx")
	{
		// ”wŒi“o˜^
		for (const auto& bg : m_stageUseCase.getBgs()) {
			m_view->addBackGroundView(BackGroundVM(bg));
		}

		m_worldUseCase.subscribe([this](const std::shared_ptr<PlayerModel> & model) {
			::NotifyCreateObject<PlayerModel>(this->m_view, model);
		});
		m_worldUseCase.subscribe([this](const std::shared_ptr<PlayerShotModel> & model) {
			::NotifyCreateObject<PlayerShotModel>(this->m_view, model);
		});

		if (auto room = m_stageUseCase.init(m_worldUseCase)){
			m_cameraUseCase.setRoom(*room);
		}
		m_cameraUseCase.setPlayer(m_worldUseCase.getPlayer());

		m_cameraUseCase.onNextRoom().subscribe([&](CameraUseCase * camera) {
			if (auto next = m_stageUseCase.initRoom(m_worldUseCase)) {
				Vec2 pos = m_worldUseCase.getPlayer()->getPos();
				camera->startCameraWork(*next, pos);
			}
		});

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


