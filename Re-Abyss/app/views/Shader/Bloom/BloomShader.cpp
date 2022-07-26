#include <abyss/views/Shader/Bloom/BloomShader.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

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
        RenderTexture m_scene;
        RenderTexture m_blurA, m_blurB;
    };
    BloomShader::BloomShader() :
        m_pImpl(std::make_shared<Impl>())
    {
    }

    void BloomShader::apply(const s3d::Texture& tex) const
    {
        m_pImpl->apply(tex);
    }
}
