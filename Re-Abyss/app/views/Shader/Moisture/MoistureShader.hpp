#pragma once
#include <memory>
#include <Siv3D/Texture.hpp>

namespace abyss
{
    class MoistureShader
    {
        class Impl;
    public:
        MoistureShader();
        ~MoistureShader();

        void apply(const s3d::Texture& tex) const;

    private:
        std::unique_ptr<Impl> m_pImpl;
    };
}
