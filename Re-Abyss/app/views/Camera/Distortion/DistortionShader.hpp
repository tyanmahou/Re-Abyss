#pragma once
#include <memory>

namespace abyss
{
    class DistortionShader
    {
        class Impl;
    public:
    private:
        std::shared_ptr<Impl> m_pImpl;
    };
}