#include <abyss/scenes/Scene/Experiment/Scene.hpp>
#if ABYSS_DEVELOP
#include <abyss/debugs/Debug.hpp>
#include <Siv3D.hpp>

#include <abyss/utils/Math/Complex.hpp>
namespace abyss::Scene::Experiment
{
    class Scene::Impl
    {
    public:
        Impl(const InitData& init) :
            m_data(init._s)
        {
            m_data->fader.fadeIn();
        }

        void update()
        {
            if (KeyEnter.down()) {
                m_data->isRequestedSceneEnd = true;
            }
        }
        void draw()
        {
            m_font(U"[Experiment] Push Enter Start").draw();
            {
                Vec2 pos{ 300, 200 };
                Vec2 posEnd{ 400, 300 };

                s3d::Circle(pos.lerp(posEnd, s3d::Periodic::Triangle0_1(2s)), 10).draw();
                s3d::Circle({300, 300}, 100).drawFrame();
            }
            {
                Vec2 pos{ 500, 200 };
                Vec2 posEnd{ 600, 300 };

                s3d::Circle(Slerp(pos, posEnd, s3d::Periodic::Triangle0_1(2s)), 10).draw();
                s3d::Circle({ 500, 300 }, 100).drawFrame();
            }
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
