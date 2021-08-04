#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss::Env
{
    class SkyShader
    {
        class Impl;
        std::shared_ptr<Impl> m_pImpl;
    public:
        SkyShader();
        SkyShader& setTime(double time);
        const SkyShader& setMultiply(double multiply) const;
        s3d::ScopedCustomShader2D start() const;
    };
}