#include <abyss/scenes/Scene/Experiment/Scene.hpp>
#if ABYSS_DEVELOP
#include <abyss/scenes/Scene/Experiment/Booter.hpp>
#include <abyss/scenes/Sys/System.hpp>
#include <abyss/commons/Factory/System/Injector.hpp>
#include <abyss/debugs/Debug.hpp>
#include <Siv3D.hpp>

#include <abyss/utils/Math/Complex.hpp>
#include <abyss/utils/Math/DualComplex.hpp>
#include <abyss/utils/Math/InterpUtil.hpp>

namespace abyss::Scene::Experiment
{
    class ComplexTest
    {
    public:
        void draw() const
        {
            Vec2 p0 = { 50, -200 };
            Vec2 p1 = { 200, -50 };
            auto t = s3d::Periodic::Triangle0_1(8s);
            {
                Vec2 center = { 750 - 200, 300 };
                auto transformer = Complex::RotateDeg(0).slerp(Complex::RotateDeg(180), t);
                Vec2 cx = transformer.transform({ 0, 0 });
                Vec2 p0x = transformer.transform(p0);
                Vec2 p1x = transformer.transform(p1);
                Triangle(center + cx, center + p0x, center + p1x).draw(ColorF(1, 1));
            }
            {
                Vec2 center = { 750 - 200, 300 };
                auto transformer = DualComplex::RotateDeg(0).sclerp(DualComplex::RotateDeg(180), t);
                Vec2 cx = transformer.transform({ 0, 0 });
                Vec2 p0x = transformer.transform(p0);
                Vec2 p1x = transformer.transform(p1);
                Triangle(center + cx, center + p0x, center + p1x).draw(ColorF(Palette::Red, 0.5));
            }
            {
                Vec2 center = { 350 + 600, 300 };
                auto before = Mat3x2::Rotate(0);
                auto after = Mat3x2::Rotate(s3d::Math::Pi);

                auto transformer = InterpUtil::Lerp(before, after, t);
                Vec2 p0x = transformer.transformPoint(p0);
                Vec2 p1x = transformer.transformPoint(p1);
                Triangle(center, center + p0x, center + p1x).draw();
            }
        }
    };
    class Scene::Impl final :
        public Cycle::Experiment::IMasterObserver
    {
    public:
        Impl(const InitData& init) :
            m_data(init._s)
        {
        }

        void init()
        {
            m_system = Factory::System::Experiment(m_data.get())
                .instantiate<Sys::System>();
            m_system->boot<Booter>(this);
        }
        void update()
        {
            m_system->update();
        }
        void draw()
        {
            m_system->draw();
        }
        bool onExit() override
        {
            m_data->isRequestedSceneEnd = true;
            return true;
        }
    private:
        std::shared_ptr<Sys::System> m_system;
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
