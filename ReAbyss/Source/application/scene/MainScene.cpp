#include "MainScene.hpp"

#include<domain/usecase/StageUseCase.hpp>

#include <presentation/presenter/MainPresenter.hpp>
#include <presentation/view/main/MainSceneView.hpp>
#include <presentation/view/main/StageView.hpp>
#include <presentation/view/main/CameraView.hpp>
namespace abyss
{
	namespace di
	{
		void Create(const String& stageFilePath)
		{
			// stage
			auto stageDataStore = std::make_unique<TiledStageDataStore>(stageFilePath);
			auto stageRepository = std::make_unique<StageRepository>(*stageDataStore);
			auto stageUseCase = std::make_unique<StageUseCase>(std::move(stageRepository));
			// camera
			auto cameraUseCase = std::make_unique<CameraUseCase>();

			auto mainPresenter = std::make_shared<MainPresenter>();

			// View
			auto mainView = std::make_unique<MainSceneView>(mainPresenter);

			auto stageView = std::make_unique<TiledStageView>(stageDataStore->getTiledMap());
			mainView->setStageView(std::move(stageView));

			auto cameraView = std::make_unique<CameraView>(&cameraUseCase->getCamera());
			mainView->setCameraView(std::move(cameraView));

		}
	}

	class MainScene::Controller
	{
		std::shared_ptr<IMainPresenter> m_presenter;
		std::unique_ptr<IMainSceneView> m_view;

	public:
		Controller([[maybe_unused]]const MainScene::InitData& init)/* :
			m_view(std::make_shared<MainView>()),
			m_presenter(std::make_unique<MainPresenter>(m_view))*/
		{
			//SoundAsset::Register(L"test", L"resources/sounds/bgms/stage_0.wav");
			//SoundAsset(L"test").setLoop(true);
			//SoundAsset(L"test").play();

			// U"work/stage0/stage0.tmx"
		}


		void init()
		{
			this->update();
		}

		void update()
		{
			//m_presenter->update();
			//m_view->update();
		}

		void draw() const
		{
			//m_view->draw();
		}
	};
	MainScene::MainScene(const InitData& init) :
		ISceneBase(init),
		m_pImpl(std::make_unique<Controller>(init))
	{
	}

	void MainScene::update()
	{
		m_pImpl->update();
	}
	void MainScene::draw() const
	{
		m_pImpl->draw();
	}
}