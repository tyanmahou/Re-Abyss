#include "DistortionShader.hpp"
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace
{
    struct ShaderParam
    {
        Float2 textureSize;
        Float2 _unused;
    };
}
namespace abyss
{
    class DistortionShader::Impl
    {
    public:
        Impl() :
            m_ps(Resource::Assets::Main()->load(U"distortion.hlsl"))
        {}
        void setDistTexture(const s3d::Texture& dist)
        {
            m_dist = dist;
            m_cb->textureSize = dist.size();
        }
        s3d::ScopedCustomShader2D start() const
        {
            s3d::Graphics2D::SetPSTexture(1, m_dist);
            s3d::Graphics2D::SetConstantBuffer(s3d::ShaderStage::Pixel, 1, m_cb);
            return ScopedCustomShader2D(m_ps);
        }
    private:
        PixelShader m_ps;
        ConstantBuffer<ShaderParam> m_cb;
        s3d::Texture m_dist;
    };

    DistortionShader::DistortionShader():
        m_pImpl(std::make_shared<Impl>())
    {}

    const DistortionShader& DistortionShader::setDistTexture(const s3d::Texture& dist) const
    {
        m_pImpl->setDistTexture(dist);
        return *this;
    }

    s3d::ScopedCustomShader2D DistortionShader::start() const
    {
        return m_pImpl->start();
    }
}
