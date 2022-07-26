#pragma once
#include <abyss/views/Shader/Bloom/BloomShader.hpp>

namespace abyss::Sfx
{
    class Bloom
    {
    public:
        Bloom();

        void apply(const s3d::Texture& tex) const;
    private:
        BloomShader m_bloomShader;
    };
}
