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
        static constexpr Point Size = Constants::GameScreenSize.asPoint();
    public:
        Impl():
            m_ps(Resource::Assets::Norelease()->load(U"bloom_brightness.hlsl")),
            m_blurA(Size),
            m_blurB(Size)
        {}
        void setLightColor(const s3d::ColorF& color)
        {
            m_cb->lightColor = color.toFloat4();
        }
        void apply(const s3d::Texture& tex) 
        {
            // 描画
            tex.draw();

            // 輝度抽出
            {
                s3d::ScopedRenderTarget2D target(m_blurA.clear(ColorF(0, 1)));
                s3d::ScopedCustomShader2D scopedShader(m_ps);
                s3d::Graphics2D::SetConstantBuffer(s3d::ShaderStage::Pixel, 1, m_cb);
                tex.draw();
            }
            {
                s3d::Shader::GaussianBlur(m_blurA, m_blurB, m_blurA);
            }
            // 加算描画
            {
                s3d::ScopedRenderStates2D blend(BlendState::Additive);
                m_blurA.draw();
            }
        }
    private:
        PixelShader m_ps;
        ConstantBuffer<ShaderParam> m_cb;
        RenderTexture m_blurA, m_blurB;
    };
    BloomShader::BloomShader() :
        m_pImpl(std::make_unique<Impl>())
    {
    }

    BloomShader::~BloomShader()
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
