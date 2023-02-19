#include <abyss/scenes/Scene/Experiment/Scene.hpp>
#if ABYSS_DEVELOP
#include <abyss/debugs/Debug.hpp>
#include <abyss/views/util/VertexUtil/VertexUtil.hpp>
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
            VertexUtil::DrawCircleFrameGiza(Circle(s3d::Scene::CenterF(), 200.0), 0, 0, 100, 100, [](s3d::Vertex2D* o, s3d::Vertex2D* i, float c, float s) {
                i->color.set(1, 1, 1, 1);
                o->color.set(1, 1, 1, 1);
            });

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
