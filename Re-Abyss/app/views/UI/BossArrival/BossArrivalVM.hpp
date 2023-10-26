#pragma once
#include <abyss/views/Shader/BossArrival/BossArrivalShader.hpp>

namespace abyss::UI::BossArrival
{
    class BossArrivalVM
    {
    public:
        BossArrivalVM();

        BossArrivalVM& setPos(const s3d::Vec2& pos);

        BossArrivalVM& setTimeRate(double timeRate)
        {
            m_timeRate = timeRate;
            return *this;
        }
        void draw() const;
    private:
        Font m_font;
        BossArrivalShader m_shader;
        double m_timeRate = 0;
    };
}
