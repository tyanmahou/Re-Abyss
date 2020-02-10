#include "MainScene.hpp"

namespace abyss
{

	class MainScene::Controller
	{
	public:
		Controller([[maybe_unused]] const MainScene::InitData& init)
		{}


		void init()
		{
		}

		void update()
		{
		}

		void draw() const
		{
			Circle(Window::ClientCenter(), 30).draw();
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