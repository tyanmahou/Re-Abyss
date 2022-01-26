#include <abyss/views/Shader/Dither/DitherShader.hpp>
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace
{
    Image g_ditherImage = []
    {
        Image image(4, 4);
        double dither[4][4] = {
            {1, 13, 4, 16},
            {9, 5, 12, 8},
            {3, 15, 2, 14},
            {11, 7, 10, 6},
        };
        for (int32 y : step(0, 4)) {
            for (int32 x : step(0, 4)) {
                image[y][x] = ColorF(dither[y][x] / 17.0);
            }
        }
        return image;
    }();
}

namespace abyss
{
    class DitherShader::Impl
    {
    public:
        Impl() :
            m_ps(Resource::Assets::Norelease()->load(U"dither.hlsl")),
            m_dither(g_ditherImage)
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
    DitherShader::DitherShader():
        m_pImpl(std::make_shared<Impl>())
    {}
    s3d::ScopedCustomShader2D DitherShader::start() const
    {
        return m_pImpl->start();
    }
}