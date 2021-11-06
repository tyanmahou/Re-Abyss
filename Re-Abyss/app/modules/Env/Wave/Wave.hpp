#pragma once
#include <abyss/views/Shader/Wave/WaveShader.hpp>

namespace abyss::Env
{
    class Wave
    {
    public:
        void update(double dt);
        void apply(std::function<void()> drawer) const;
    private:
        double m_time = 0.0;
        WaveShader m_shader;
    };
}