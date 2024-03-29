#pragma once
#include <memory>
#include <Siv3D/Fwd.hpp>
#include <Siv3D/ScopedCustomShader2D.hpp>

namespace abyss
{
    class DecorFarShader
    {
        class Impl;
    public:
        DecorFarShader();
        ~DecorFarShader();

        const DecorFarShader& setTime(double time) const;

        s3d::ScopedCustomShader2D start() const;

    private:
        std::unique_ptr<Impl> m_pImpl;
    };
}
