#include <abyss/views/Shader/DecorFar/DecorFarShader.hpp>
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace
{
    struct ShaderParam
    {
        float timer = 0;
    };
}
namespace abyss
{
    class DecorFarShader::Impl
    {
    public:
        Impl() :
            m_ps(Resource::Assets::NoRelease()->load(U"decor_far.hlsl"))
        {
        }
        void setTime(double time)
        {
            m_cb->timer = static_cast<float>(time);
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
    DecorFarShader::DecorFarShader():
        m_pImpl(std::make_unique<Impl>())
    {}
    DecorFarShader::~DecorFarShader()
    {
    }
    const DecorFarShader& DecorFarShader::setTime(double time) const
    {
        m_pImpl->setTime(time);
        return *this;
    }
    s3d::ScopedCustomShader2D DecorFarShader::start() const
    {
        return m_pImpl->start();
    }
}
