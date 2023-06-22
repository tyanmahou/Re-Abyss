#include <abyss/scenes/Scene/Experiment/Scene.hpp>
#if ABYSS_DEVELOP
#include <abyss/debugs/Debug.hpp>
#include <Siv3D.hpp>

#include <abyss/utils/Math/Complex.hpp>
#include <abyss/utils/Math/InterpUtil.hpp>

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
            Vec2 s = s3d::Circular0(100, s3d::ToRadians(0));
            Vec2 e = s3d::Circular0(100, s3d::ToRadians(180));
            auto t = s3d::Periodic::Triangle0_1(2s);
            {
                Vec2 center = { 200, 300 };
                s3d::Circle(center + s.lerp(e, t), 10).draw();
                s3d::Circle(center, 100).drawFrame();
            }
            auto r = Complex::RotateDeg(180);
            {
                Vec2 center = { 450, 300 };
                s3d::Circle(center + InterpUtil::AngleSlerp(s, e, t), 10).draw();
                s3d::Circle(center, 100).drawFrame();
            }
            {
                Vec2 center = { 700, 300 };
                s3d::Circle(center + InterpUtil::Nlerp(s, e, t), 10).draw();
                s3d::Circle(center, 100).drawFrame();
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
