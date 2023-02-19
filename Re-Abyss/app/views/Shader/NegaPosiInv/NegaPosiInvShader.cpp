#include <abyss/views/Shader/NegaPosiInv/NegaPosiInvShader.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss
{
    class NegaPosiInvShader::Impl
    {
    public:
        Impl() :
            m_ps(Resource::Assets::Norelease()->load(U"negaposi_inv.hlsl"))
        {}
        void setMaskTexture(const s3d::Texture& mask)
        {
            m_mask = mask;
        }
        s3d::ScopedCustomShader2D start() const
        {
            s3d::Graphics2D::SetPSTexture(1, m_mask);
            return ScopedCustomShader2D(m_ps);
        }
    private:
        PixelShader m_ps;
        s3d::Texture m_mask;
    };

    NegaPosiInvShader::NegaPosiInvShader() :
        m_pImpl(std::make_unique<Impl>())
    {}
    NegaPosiInvShader::~NegaPosiInvShader()
    {
    }
    const NegaPosiInvShader& abyss::NegaPosiInvShader::setMaskTexture(const s3d::Texture& mask) const
    {
        m_pImpl->setMaskTexture(mask);
        return *this;
    }
    s3d::ScopedCustomShader2D NegaPosiInvShader::start() const
    {
        return m_pImpl->start();
    }
}
