#pragma once
#include <memory>
#include <functional>
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss
{
    class SkyShader
    {
        class Impl;
        std::shared_ptr<Impl> m_pImpl;
    public:
        SkyShader();
        s3d::ScopedCustomShader2D start() const;
    };
}