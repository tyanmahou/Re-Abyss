#include "ScanlineShader.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace
{
    struct ShaderParam
    {
        Float2 textureSize;
        float timer;
    };
}
namespace abyss
{
    class ScanlineShader::Impl
    {
    public:
        Impl() :
            m_ps(Resource::Assets::Norelease()->load(U"scanline.hlsl"))
        {
            m_cb->textureSize = static_cast<Float2>(Scene::Size());
        }
        void setTime(double time)
        {
            m_cb->timer = static_cast<float>(time);
        }
        void setTexturSize(const s3d::Vec2& size)
        {
            m_cb->textureSize = static_cast<Float2>(size);
        }
        ScopedCustomShader2D start()
        {
            s3d::Graphics2D::SetConstantBuffer(s3d::ShaderStage::Pixel, 1, m_cb);
            return ScopedCustomShader2D(m_ps);
        }
    private:
        PixelShader m_ps;
        ConstantBuffer<ShaderParam> m_cb;
    };
    ScanlineShader::ScanlineShader():
        m_pImpl(std::make_shared<Impl>())
    {}
    const ScanlineShader& ScanlineShader::setTime(double time) const
    {
        m_pImpl->setTime(time);
        return *this;
    }
    const ScanlineShader& ScanlineShader::setTexturSize(const s3d::Vec2& size) const
    {
        m_pImpl->setTexturSize(size);
        return *this;
    }
    s3d::ScopedCustomShader2D ScanlineShader::start() const
    {
        return m_pImpl->start();
    }
}