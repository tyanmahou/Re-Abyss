#include <abyss/scenes/Scene/Experiment/Scene.hpp>

namespace abyss::Scene::Experiment
{
    class Scene::Impl
    {
        std::shared_ptr<Data_t> m_data;
    public:
        Impl([[maybe_unused]] const InitData& init) :
            m_data(init._s)
        {}

        void update()
        {
            if (KeyEnter.down()) {
                m_data->isRequestedSceneEnd = true;
            }
        }
        void draw()
        {

        }
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
