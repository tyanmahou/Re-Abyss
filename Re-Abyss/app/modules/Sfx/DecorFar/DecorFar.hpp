#pragma once
#include <abyss/views/Shader/DecorFar/DecorFarShader.hpp>

namespace abyss::Sfx
{
    class DecorFar
    {
    public:
        void update(double dt);
        s3d::ScopedCustomShader2D start() const;
    private:
        double m_time = 0;
        DecorFarShader m_shader;
    };
}
