#include <abyss/scenes/Scene/StageResult/Scene.hpp>

namespace abyss::Scene::StageResult
{
	class Scene::Impl
	{
	public:
		Impl([[maybe_unused]] const InitData& init):
			m_data(init._s)
		{}
	private:
		std::shared_ptr<Data_t> m_data;
	};

    Scene::Scene(const InitData& init) :
		ISceneBase(init),
		m_pImpl(std::make_unique<Impl>(init))
	{}

    Scene::~Scene()
	{
	}

	void Scene::onSceneUpdate()
	{
	}

	void Scene::onSceneDraw() const
	{
	}
}
