#include <abyss/views/Shader/Dither/DitherShader.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/views/Shader/util/BayerMatrix.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    class DitherShader::Impl
    {
    public:
        Impl() :
            m_ps(Resource::Assets::Norelease()->load(U"dither.hlsl")),
            m_dither(BayerMatrix::Texture())
        {}
        ScopedCustomShader2D start() const
        {
            s3d::Graphics2D::SetPSTexture(3, m_dither);
            return ScopedCustomShader2D(m_ps);
        }
    private:
        PixelShader m_ps;
        s3d::Texture m_dither;
    };
    DitherShader::DitherShader() :
        m_pImpl(std::make_shared<Impl>())
    {}
    s3d::ScopedCustomShader2D DitherShader::start() const
    {
        return m_pImpl->start();
    }
}
