#include <abyss/views/Shader/Bloom/BloomShader.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace
{
    struct ShaderParam
    {
        Float4 lightColor;
    };
}

namespace abyss
{
    class BloomShader::Impl
    {
    public:
        Impl():
            m_ps(Resource::Assets::Norelease()->load(U"bloom_brightness.hlsl")),
            m_scene(Constants::GameScreenSize.asPoint()),
            m_blurA(Constants::GameScreenSize.asPoint()),
            m_blurB(Constants::GameScreenSize.asPoint())
        {}
        void setLightColor(const s3d::ColorF& color)
        {
            m_cb->lightColor = color.toFloat4();
        }
        void apply(const s3d::Texture& tex) 
        {
            {
                s3d::ScopedRenderTarget2D target(m_scene.clear(ColorF(0, 1)));
                BlendState b = BlendState::Default2D;
                b.srcAlpha = Blend::One;
                b.dstAlpha = Blend::One;
                b.opAlpha = BlendOp::Max;
                s3d::ScopedRenderStates2D blend(b);
                s3d::ScopedCustomShader2D scopedShader(m_ps);
                s3d::Graphics2D::SetConstantBuffer(s3d::ShaderStage::Pixel, 1, m_cb);
                tex.draw();
            }
            {
                s3d::Shader::GaussianBlur(m_scene, m_blurA, m_blurB);
            }
            tex.draw();
            {
                s3d::ScopedRenderStates2D blend(BlendState::Additive);
                m_blurB.draw();
            }
        }
    private:
        PixelShader m_ps;
        ConstantBuffer<ShaderParam> m_cb;
        RenderTexture m_scene;
        RenderTexture m_blurA, m_blurB;
    };
    BloomShader::BloomShader() :
        m_pImpl(std::make_shared<Impl>())
    {
    }

    const BloomShader& BloomShader::setLightColor(const s3d::ColorF& color) const
    {
        m_pImpl->setLightColor(color);
        return *this;
    }

    void BloomShader::apply(const s3d::Texture& tex) const
    {
        m_pImpl->apply(tex);
    }
}
