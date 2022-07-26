#pragma once
#pragma once
#include <memory>
#include <Siv3D/ScopedCustomShader2D.hpp>

namespace abyss
{
    class BloomShader
    {
        class Impl;
    public:
        BloomShader();

        void apply(const s3d::Texture& tex) const;
    private:
        std::shared_ptr<Impl> m_pImpl;
    };
}
