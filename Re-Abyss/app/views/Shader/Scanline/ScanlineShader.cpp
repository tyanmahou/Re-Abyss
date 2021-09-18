#include "ScanlineShader.hpp"
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace
{
    struct ShaderParam
    {
        Float2 textureSize;
        float timer;
        float _unused;
    };
}
namespace abyss
{
    class ScanlineShader::Impl
    {
    public:
        Impl() :
            m_ps(Resource::Assets::Main()->load(U"scanline.hlsl"))
        {}
        ScopedCustomShader2D start()
        {
            m_cb->textureSize = Scene::Size();
            m_cb->timer = Scene::Time();
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
    s3d::ScopedCustomShader2D ScanlineShader::start() const
    {
        return m_pImpl->start();
    }
}