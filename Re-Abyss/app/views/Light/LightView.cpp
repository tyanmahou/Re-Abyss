#include "LightView.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/views/Camera/CameraView.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

#include <abyss/debugs/Menu/Menu.hpp>

namespace
{
    Image CreateDither()
    {
        Image image(4, 4);
        constexpr double dither[4][4] = {
            {1, 13, 4, 16},
            {9, 5, 12, 8},
            {3, 15, 2, 14},
            {11, 7, 10, 6},
        };
        for (int32 y : step(0, 4)) {
            for (int32 x : step(0, 4)) {
                image[y][x] = ColorF(dither[y][x] / 17.0);
            }
        }
        return image;
    }
}

namespace abyss
{
    class LightShader
    {
    public:
        LightShader():
            m_ps(Resource::Assets::Main()->loadPs(U"light.hlsl")),
            m_dither(::CreateDither())
        {

        }
        LightShader& setLightsTexture(const s3d::Texture& lights)
        {
            m_lights = lights;
            return *this;
        }
        ScopedCustomShader2D start()
        {
            s3d::Graphics2D::SetTexture(1, m_dither);
            s3d::Graphics2D::SetTexture(2, m_lights);
            return ScopedCustomShader2D(m_ps);
        }
    private:
        PixelShader m_ps;
        s3d::Texture m_dither;
        s3d::Texture m_lights;
    };

    LightView::LightView():
        m_rt(Constants::GameScreenSize_v<uint32>.x, Constants::GameScreenSize_v<uint32>.y),
        m_shader(std::make_shared<LightShader>())
    {
        m_rt.clear(ColorF(0.0, 1.0));
    }
    void LightView::clear()
    {
        m_rights.clear();
    }
    void LightView::push(const LightVM & light)
    {
        m_rights.push_back(light);
    }
    void LightView::draw(const s3d::Texture& dest, double time) const
    {
        {
            ScopedRenderTarget2D target(m_rt);
            ScopedRenderStates2D state(BlendState::Additive);
            m_rt.clear(ColorF(0, 1));
            for (const auto& light : m_rights) {
                light.draw(time);
            }
        }
        {
            Transformer2D t2d(Mat3x2::Identity(), Transformer2D::Target::SetLocal);

#if ABYSS_DEBUG
            if (Debug::Menu::IsDebug(U"disable-darkness")) {
                dest.draw();
                return;
            }
#endif
            auto ps = m_shader
                ->setLightsTexture(m_rt)
                .start();
            dest.draw();
        }
    }
}
