#include <abyss/modules/Sfx/Moisture/Moisture.hpp>
#include <abyss/commons/Constants.hpp>
#include <Siv3D.hpp>

namespace abyss::Sfx
{
    class Moisture::Impl
    {
        static constexpr Point Size = Constants::GameScreenSize.asPoint();
    public:
        Impl() :
            m_scene(Size),
            m_blurA(Size),
            m_blurB(Size),
            m_blur4A(Size / 4),
            m_blur4B(Size / 4)
        {}
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
        }
    private:
        RenderTexture m_scene;
        RenderTexture m_blurA, m_blurB;
        RenderTexture m_blur4A, m_blur4B;
    };
    Moisture::Moisture():
        m_pImpl(std::make_shared<Impl>())
    {
    }
    void Moisture::apply(const s3d::Texture& tex) const
    {
        m_pImpl->apply(tex);
    }
}
