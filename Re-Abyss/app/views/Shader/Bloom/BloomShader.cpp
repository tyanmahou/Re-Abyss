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
            m_scene(Size),
            m_blurA(Size),
            m_blurB(Size),
            m_blur4A(Size / 4),
            m_blur4B(Size / 4),
            m_blurC(Size),
            m_blurD(Size)
        {}
        void setLightColor(const s3d::ColorF& color)
        {
            m_cb->lightColor = color.toFloat4();
        }
        void apply(const s3d::Texture& tex) 
        {
            // 元シーンのぼかしを生成
            {
                s3d::Shader::GaussianBlur(tex, m_blurB, m_blurA);
                Shader::Downsample(m_blurA, m_blur4A);
                s3d::Shader::GaussianBlur(m_blur4A, m_blur4B, m_blur4A);
            }
            // ぼかしとmax合成
            {
                s3d::ScopedRenderTarget2D target(m_scene.clear(ColorF(0, 1)));
                BlendState b{
                    true,
                    Blend::One,
                    Blend::One,
                    BlendOp::Max
                };
                s3d::ScopedRenderStates2D blend(b, SamplerState::BorderLinear);
                tex.draw();
                m_blur4A.resized(Size).draw(ColorF(0.8));
            }
            // 描画
            m_scene.draw();

            // 輝度抽出
            {
                s3d::ScopedRenderTarget2D target(m_blurC.clear(ColorF(0, 1)));
                s3d::ScopedCustomShader2D scopedShader(m_ps);
                s3d::Graphics2D::SetConstantBuffer(s3d::ShaderStage::Pixel, 1, m_cb);
                m_scene.draw();
            }
            {
                s3d::Shader::GaussianBlur(m_blurC, m_blurD, m_blurC);
            }
            // 加算描画
            {
                s3d::ScopedRenderStates2D blend(BlendState::Additive);
                m_blurC.draw();
            }
        }
    private:
        PixelShader m_ps;
        ConstantBuffer<ShaderParam> m_cb;
        RenderTexture m_scene;
        RenderTexture m_blurA, m_blurB;
        RenderTexture m_blur4A, m_blur4B;
        RenderTexture m_blurC, m_blurD;
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
