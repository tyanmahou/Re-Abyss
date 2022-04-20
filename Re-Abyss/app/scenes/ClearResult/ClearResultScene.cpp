#include <abyss/scenes/ClearResult/ClearResultScene.hpp>

namespace abyss
{
	class ClearResultScene::Impl
	{
	public:
		Impl([[maybe_unused]] const InitData& init)
		{
		}
	private:

	};

	ClearResultScene::ClearResultScene(const InitData& init) :
		ISceneBase(init),
		m_pImpl(std::make_unique<Impl>(init))
	{}

	ClearResultScene::~ClearResultScene()
	{
	}

	void ClearResultScene::onSceneUpdate()
	{
	}

	void ClearResultScene::onSceneDraw() const
	{
	}
}
