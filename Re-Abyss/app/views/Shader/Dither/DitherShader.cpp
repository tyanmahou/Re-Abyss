#include <abyss/views/Shader/Dither/DitherShader.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/views/Shader/util/BayerMatrix.hpp>
#include <Siv3D.hpp>

namespace
{
    struct ShaderParam
    {
        bool isShape = false;
        abyss::DitherShader::Kind kind = abyss::DitherShader::Kind::Default;
    };
}
namespace abyss
{
    class DitherShader::Impl
    {
    public:
        Impl() :
            m_ps(Resource::Assets::Norelease()->load(U"dither.hlsl")),
            m_dither(BayerMatrix::Texture())
        {
        }
        void setIsShape(bool isShape)
        {
            m_cb->isShape = isShape;
        }
        void setKind(Kind kind)
        {
            m_cb->kind = kind;
        }
        ScopedCustomShader2D start() const
        {
            s3d::Graphics2D::SetPSConstantBuffer(1, m_cb);
            s3d::Graphics2D::SetPSTexture(3, m_dither);
            return ScopedCustomShader2D(m_ps);
        }
    private:
        PixelShader m_ps;
        ConstantBuffer<ShaderParam> m_cb;
        s3d::Texture m_dither;
    };
    DitherShader::DitherShader() :
        m_pImpl(std::make_unique<Impl>())
    {}
    DitherShader::~DitherShader()
    {
    }
    const DitherShader& DitherShader::setIsShape(bool isShape) const
    {
        m_pImpl->setIsShape(isShape);
        return *this;
    }
    const DitherShader& DitherShader::setKind(Kind kind) const
    {
        m_pImpl->setKind(kind);
        return *this;
    }
    s3d::ScopedCustomShader2D DitherShader::start() const
    {
        return m_pImpl->start();
    }
}
