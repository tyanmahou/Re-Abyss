#include "MainScene.hpp"

#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/factories/ActionSystem/ActionSystemFactory.hpp>

namespace abyss
{
	class MainScene::Controller
	{
		std::unique_ptr<ActionSystem> m_actionSystem;

	public:
		Controller([[maybe_unused]] const MainScene::InitData& init):
			m_actionSystem(ActionSystemFactory::CreateFromTmx(U"resources/maps/stage0.tmx"))
		{
			this->init();
		}

		void init()
		{
			m_actionSystem->init();
		}

		void update()
		{
			m_actionSystem->update();
		}

		void draw() const
		{
			m_actionSystem->draw();
		}
	};

	MainScene::MainScene(const InitData& init) :
		ISceneBase(init),
		m_pImpl(std::make_unique<Controller>(init))
	{}

	void MainScene::update()
	{
		m_pImpl->update();
	}
	void MainScene::draw() const
	{
		m_pImpl->draw();
	}
}