#include "MainScene.hpp"

#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/controllers/Stage/Stage.hpp>
#include <abyss/datastores/Stage/StageDataStore.hpp>
#include <abyss/repositories/Stage/StageRepository.hpp>

namespace abyss::di
{
    std::unique_ptr<ActionSystem> CreateActionSystem(const FilePath& stageTmx)
    {
        // stage
        auto stageDataStore = std::make_unique<TiledStageDataStore>(stageTmx);
        auto stageRepository = std::make_unique<StageRepository>(*stageDataStore);
		auto stage = std::make_unique<Stage>(std::move(stageRepository));
		return std::make_unique<ActionSystem>(std::move(stage));
    }
}
namespace abyss
{
	class MainScene::Controller
	{
		std::unique_ptr<ActionSystem> m_actionSystem;

	public:
		Controller([[maybe_unused]] const MainScene::InitData& init):
			m_actionSystem(di::CreateActionSystem(U"work/stage0/stage0.tmx"))
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