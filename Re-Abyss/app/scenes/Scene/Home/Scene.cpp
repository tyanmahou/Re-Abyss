#include <abyss/scenes/Scene/Home/Scene.hpp>
#include <abyss/debugs/Debug.hpp>
#include <Siv3D.hpp>

namespace abyss::Scene::Home
{
    class Scene::Impl
    {
    public:
        Impl(const InitData& init) :
            m_data(init._s)
        {}

        void update()
        {
        }
        void draw()
        {
        }
    private:
        std::shared_ptr<Data_t> m_data;
    };
    Scene::Scene(const InitData& init) :
        ISceneBase(init),
        m_pImpl(std::make_unique<Impl>(init))
    {
    }
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
