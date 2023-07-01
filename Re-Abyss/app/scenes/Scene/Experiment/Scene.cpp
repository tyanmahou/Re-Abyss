#include <abyss/scenes/Scene/Experiment/Scene.hpp>
#if ABYSS_DEVELOP
#include <abyss/debugs/Debug.hpp>
#include <Siv3D.hpp>

#include <abyss/utils/Math/Complex.hpp>
#include <abyss/utils/Math/DualComplex.hpp>
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
            Vec2 p0 = { 50, -200 };
            Vec2 p1 = { 200, -50 };
            auto t = s3d::Periodic::Triangle0_1(8s);
            {
                Vec2 center = { 750-200, 300 };
                auto transformer = Complex::RotateDeg(0).slerp(Complex::RotateDeg(180), t);
                Vec2 cx = transformer.transform({0, 0});
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
            //m_font(U"[Experiment] Push Enter Start").draw();
            //Vec2 s = s3d::Circular0(100, s3d::ToRadians(0));
            //Vec2 e = s3d::Circular0(100, s3d::ToRadians(170));
            //auto t = s3d::Periodic::Triangle0_1(8s);
            //{
            //    Vec2 center = { 750, 300 };
            //    auto color = Palette::White;
            //    auto cp = Complex::RotateDeg(0).lerp(Complex::RotateDeg(190), t);
            //    auto pos = center + s * cp;
            //    s3d::Circle(pos, 10).draw(color);

            //    s3d::Circle(center, 100).drawFrame();
            //}
            //{
            //    Vec2 center = { 750, 300 };
            //    auto color = Palette::White;
            //    auto cp = Complex::RotateDeg(0).slerp(Complex::RotateDeg(190), t);
            //    auto pos = center + s * cp;
            //    s3d::Circle(pos, 10).draw(color);

            //    s3d::Circle(center, 100).drawFrame();
            //}
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
