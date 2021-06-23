#pragma once
#include <memory>
#include <Siv3D/Fwd.hpp>

namespace abyss
{
    class DitherShader
    {
        class Impl;
    public:
        DitherShader();

        s3d::ScopedCustomShader2D start() const;

    private:
        std::shared_ptr<Impl> m_pImpl;
    };
}