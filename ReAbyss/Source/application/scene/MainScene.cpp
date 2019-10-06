#include "MainScene.hpp"

#include<domain/usecase/StageUseCase.hpp>

//#include "../../presentation/presenter/MainPresenter.hpp"
#include <presentation/view/main/MainView.hpp>

namespace abyss
{
	namespace di
	{
		void Create(const String& stageFilePath)
		{
			auto stageDataStore = std::make_unique<TiledStageDataStore>(stageFilePath);
			auto stageRepository = std::make_unique<StageRepository>(*stageDataStore);
			auto stageUseCase = std::make_unique<StageUseCase>(std::move(stageRepository));

			// View
			auto stageView = std::make_unique<TiledStageView>(stageDataStore->getTiledMap());
		}
	}

	class MainScene::Controller
	{
		//std::shared_ptr<IMainView> m_view;
		//std::unique_ptr<IMainPresenter> m_presenter;
	public:
		Controller()/* :
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
		m_pImpl(std::make_unique<Controller>())
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