#include <abyss/scenes/Scene/Demo/Scene.hpp>

namespace abyss::Scene::Demo
{
    class Scene::Impl
    {
    public:
        Impl([[maybe_unused]]const InitData& init)
        {}

        void update()
        {
        }

        void draw() const
        {
        }
    };
    Scene::Scene(const InitData& init):
        ISceneBase(init),
        m_pImpl(std::make_unique<Impl>(init))
    {}
    Scene::~Scene()
    {}
    void Scene::onSceneUpdate()
    {
        m_pImpl->update();
    }

    void Scene::onSceneDraw() const
    {
        m_pImpl->draw();
    }
}
