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

        const DistortionShader& setDistTexture(const s3d::Texture& dist) const;
        s3d::ScopedCustomShader2D start() const;
    private:
        std::shared_ptr<Impl> m_pImpl;
    };
}