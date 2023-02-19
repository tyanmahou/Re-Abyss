#include <abyss/scenes/Scene/Experiment/Scene.hpp>
#if ABYSS_DEVELOP
#include <abyss/debugs/Debug.hpp>
#include <Siv3D.hpp>
namespace abyss::Scene::Experiment
{
    class Scene::Impl
    {
    public:
        Impl(const InitData& init) :
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
            m_font(U"[Experiment] Push Enter Start").draw();
        }
    private:
        std::shared_ptr<Data_t> m_data;
        Font m_font{ 20 };
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
#endif
