#pragma once
#include <abyss/views/Shader/Moisture/MoistureShader.hpp>

namespace abyss::Sfx
{
    class Moisture
    {
    public:
        Moisture();

        void apply(const s3d::Texture& tex) const;

    private:
        MoistureShader m_shader;
    };
}
