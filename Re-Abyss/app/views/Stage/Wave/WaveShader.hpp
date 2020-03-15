#pragma once
#include <memory>
#include <functional>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class WaveShader
    {
        class Impl;
        std::shared_ptr<Impl> m_pImpl;
    public:
        WaveShader();

        void apply(const CameraView& camera, std::function<void()> drawer) const;
    };
}