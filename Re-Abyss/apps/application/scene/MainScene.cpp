#include "MainScene.hpp"

#include "../../presentation/presenter/MainPresenter.hpp"
#include "../../presentation/view/main/MainView.hpp"

namespace abyss
{

	class MainScene::Controller
	{
		std::shared_ptr<IMainView> m_view;
		std::unique_ptr<IMainPresenter> m_presenter;
	public:
		Controller() :
			m_view(std::make_shared<MainView>()),
			m_presenter(std::make_unique<MainPresenter>(m_view))
		{
			SoundAsset::Register(L"test", L"resources/sounds/bgms/stage_0.wav");
			SoundAsset(L"test").setLoop(true);
			SoundAsset(L"test").play();
		}


		void init()
		{
			//m_model->init();
			m_view->update();
		}

		void update()
		{
			//m_model->update();
			//m_view->update();
		}

		void draw() const
		{
			m_view->draw();
		}
	};
	MainScene::MainScene() :
		m_pImpl(std::make_unique<Controller>())
	{
	}
	void MainScene::init()
	{
		m_pImpl->init();
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