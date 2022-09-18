#pragma once
#include <memory>
#include <memory>
#include <Siv3D/Fwd.hpp>

namespace abyss
{
    class DistortionShader
    {
        class Impl;
    public:
        DistortionShader();
        ~DistortionShader();

        const DistortionShader& setDistTexture(const s3d::Texture& dist) const;
        s3d::ScopedCustomShader2D start() const;
    private:
        std::unique_ptr<Impl> m_pImpl;
    };
}
