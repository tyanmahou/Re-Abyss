#include <abyss/views/Shader/RgbShift/RgbShiftShader.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    class RgbShiftShader::Impl
    {
    public:
        Impl() :
            m_ps(Resource::Assets::Norelease()->load(U"rgb_shift.hlsl"))
        {
        }
        ScopedCustomShader2D start()
        {
            return ScopedCustomShader2D(m_ps);
        }
    private:
        PixelShader m_ps;
    };

    RgbShiftShader::RgbShiftShader() :
        m_pImpl(std::make_shared<Impl>())
    {}
    s3d::ScopedCustomShader2D RgbShiftShader::start() const
    {
        return m_pImpl->start();
    }
}
