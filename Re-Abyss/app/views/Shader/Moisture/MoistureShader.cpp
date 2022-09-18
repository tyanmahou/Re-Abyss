#include <abyss/views/Shader/Moisture/MoistureShader.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    class MoistureShader::Impl
    {
        static constexpr Point Size = Constants::GameScreenSize.asPoint();
    public:
        Impl() :
            m_ps(Resource::Assets::Norelease()->load(U"moisture.hlsl")),
            m_blurA(Size),
            m_blurB(Size),
            m_blur4A(Size / 4),
            m_blur4B(Size / 4),
            m_blur8A(Size / 8),
            m_blur8B(Size / 8)
        {}
        void apply(const s3d::Texture& tex)
        {
            // 元シーンのぼかしを生成
            {
                s3d::Shader::GaussianBlur(tex, m_blurB, m_blurA);
                Shader::Downsample(m_blurA, m_blur4A);
                s3d::Shader::GaussianBlur(m_blur4A, m_blur4B, m_blur4A);
                Shader::Downsample(m_blur4A, m_blur8A);
                s3d::Shader::GaussianBlur(m_blur8A, m_blur8B, m_blur8A);
            }
            // ぼかしとmax合成
            {
                s3d::Graphics2D::SetPSTexture(1, m_blurA);
                s3d::Graphics2D::SetPSTexture(2, m_blur4A);
                s3d::Graphics2D::SetPSTexture(3, m_blur8A);
                s3d::ScopedCustomShader2D ps(m_ps);
                s3d::ScopedRenderStates2D sampler(SamplerState::BorderLinear);
                tex.draw();
            }
        }
    private:
        PixelShader m_ps;
        RenderTexture m_blurA, m_blurB;
        RenderTexture m_blur4A, m_blur4B;
        RenderTexture m_blur8A, m_blur8B;
    };
    MoistureShader::MoistureShader() :
        m_pImpl(std::make_unique<Impl>())
    {}
    MoistureShader::~MoistureShader()
    {
    }
    void MoistureShader::apply(const s3d::Texture& tex) const
    {
        m_pImpl->apply(tex);
    }
}
