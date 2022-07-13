#pragma once
#include <abyss/utils/Singleton/DynamicSingleton.hpp>
#include <Siv3D/Texture.hpp>

namespace abyss
{
    class BayerMatrix : DynamicSingleton<BayerMatrix>
    {
        friend DynamicSingleton<BayerMatrix>;
    public:
        static s3d::Texture Texture();
    private:
        BayerMatrix();
    private:
        s3d::Texture m_texture;
    };
}
