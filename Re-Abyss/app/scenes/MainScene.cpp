#include "MainScene.hpp"

#include <abyss/datastores/StageDataStore.hpp>
#include <abyss/repositories/StageRepository.hpp>

namespace abyss::di
{
    void CreateMainScene(const FilePath& stageTmx)
    {
        // stage
        auto stageDataStore = std::make_unique<TiledStageDataStore>(stageTmx);
        auto stageRepository = std::make_unique<StageRepository>(*stageDataStore);

    }
}
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