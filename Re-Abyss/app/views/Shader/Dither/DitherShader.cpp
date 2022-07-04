#include <abyss/views/Shader/Dither/DitherShader.hpp>
#include <Siv3D.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace
{
    Image g_ditherImage = []
    {
        Image image(8, 8);
        {
            constexpr double dither2x2[2][2] = {
                {1, 4},
                {3, 2},
            };
            for (int32 y : step(0, 4)) {
                for (int32 x : step(0, 4)) {
                    image[y][x].r = Color::ToUint8(dither2x2[y][x] / 5.0);
                }
            }
        }
        {
            constexpr double dither4x4[4][4] = {
                {1, 13, 4, 16},
                {9, 5, 12, 8},
                {3, 15, 2, 14},
                {11, 7, 10, 6},
            };
            for (int32 y : step(0, 4)) {
                for (int32 x : step(0, 4)) {
                    image[y][x].g = Color::ToUint8(dither4x4[y][x] / 17.0);
                }
            }
        }
        constexpr double dither8x8[8][8] = {
            {1, 33, 9, 41, 3, 35, 11, 43},
            {49, 17, 57, 25, 51, 19, 59, 27},
            {13, 45, 5, 37, 15, 47, 7, 39},
            {61, 29, 53, 21, 63, 31, 55, 23},
            {4, 36, 12, 44, 2, 34, 10, 42},
            {52, 20, 60, 28, 50, 18, 58, 26},
            {16, 48, 8, 40, 14, 46, 6, 38},
            {64, 32, 56, 24, 62, 30, 54, 22},
        };
        for (int32 y : step(0, 8)) {
            for (int32 x : step(0, 8)) {
                image[y][x].b = Color::ToUint8(dither8x8[y][x] / 65.0);
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
