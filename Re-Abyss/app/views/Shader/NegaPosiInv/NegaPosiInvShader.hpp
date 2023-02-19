#pragma once
#include <memory>
#include <Siv3D/Fwd.hpp>

namespace abyss
{
    class NegaPosiInvShader
    {
        class Impl;
    public:
        NegaPosiInvShader();
        ~NegaPosiInvShader();

        const NegaPosiInvShader& setMaskTexture(const s3d::Texture& mask) const;
        s3d::ScopedCustomShader2D start() const;
    private:
        std::unique_ptr<Impl> m_pImpl;
    };
}
