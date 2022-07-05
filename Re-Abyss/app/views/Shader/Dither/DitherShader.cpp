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
            constexpr double dither3x3[3][3] = {
                {3, 6, 2},
                {7, 1, 8},
                {4, 9, 5},
            };
            for (int32 y : step(0, 3)) {
                for (int32 x : step(0, 3)) {
                    image[y][x].g = Color::ToUint8(dither3x3[y][x] / 10.0);
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
                    image[y][x].b = Color::ToUint8(dither4x4[y][x] / 17.0);
                }
            }
        }
        constexpr double dither8x8[8][8] = {
            {1, 49, 13, 61, 4, 52, 16, 64},
            {33, 17, 45, 29, 36, 20, 48, 32},
            {9, 57, 5, 53, 12, 60, 8, 56},
            {41, 25, 37, 21, 44, 28, 40, 24},
            {3, 51, 15, 63, 2, 50, 14, 62},
            {35, 19, 47, 31, 34, 18, 46, 30},
            {11, 59, 7, 55, 10, 58, 6, 54},
            {43, 27, 39, 23, 42, 26, 38, 22},
        };
        for (int32 y : step(0, 8)) {
            for (int32 x : step(0, 8)) {
                image[y][x].a = Color::ToUint8(dither8x8[y][x] / 65.0);
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
    DitherShader::DitherShader() :
        m_pImpl(std::make_shared<Impl>())
    {}
    s3d::ScopedCustomShader2D DitherShader::start() const
    {
        return m_pImpl->start();
    }
}
