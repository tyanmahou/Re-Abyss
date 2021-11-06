#pragma once
#include <memory>
#include <functional>
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Fwd.hpp>

namespace abyss::Env
{
    class WaveShader
    {
        class Impl;
        std::shared_ptr<Impl> m_pImpl;
    public:
        WaveShader();

        const WaveShader& setTime(double time) const;
        const WaveShader& setMultiply(float multiply) const;
        ScopedCustomShader2D start() const;
        void apply(std::function<void()> drawer) const;
    };
}