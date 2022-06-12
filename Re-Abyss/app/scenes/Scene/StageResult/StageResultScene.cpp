#include <abyss/scenes/Scene/StageResult/StageResultScene.hpp>

namespace abyss
{
	class StageResultScene::Impl
	{
	public:
		Impl([[maybe_unused]] const InitData& init):
			m_data(init._s)
		{}
	private:
		std::shared_ptr<Data_t> m_data;
	};

    StageResultScene::StageResultScene(const InitData& init) :
		ISceneBase(init),
		m_pImpl(std::make_unique<Impl>(init))
	{}

    StageResultScene::~StageResultScene()
	{
	}

	void StageResultScene::onSceneUpdate()
	{
	}

	void StageResultScene::onSceneDraw() const
	{
	}
}
