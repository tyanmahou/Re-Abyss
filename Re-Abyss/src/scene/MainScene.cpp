#include "MainScene.hpp"

#include "../model/scene/MainSceneModel.hpp"
#include "../view/scene/MainSceneView.h"

namespace abyss
{

	class MainScene::Controller
	{
		std::unique_ptr<MainSceneModel> m_model;
		std::unique_ptr<MainSceneView> m_view;
	public:
		Controller() :
			m_model(std::make_unique<MainSceneModel>()),
			m_view(std::make_unique<MainSceneView>(m_model.get()))
		{
		
		}


		void init()
		{
			m_model->init();
		}

		void update()
		{
			m_model->update();
			m_view->update();
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