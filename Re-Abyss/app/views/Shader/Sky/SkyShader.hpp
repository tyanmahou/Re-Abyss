#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss
{
    class SkyShader
    {
    public:
        SkyShader();
        ~SkyShader();

        SkyShader& setTime(double time);
        const SkyShader& setMultiply(double multiply) const;
        s3d::ScopedCustomShader2D start() const;
    private:
        class Impl;
        std::unique_ptr<Impl> m_pImpl;
    };
}
