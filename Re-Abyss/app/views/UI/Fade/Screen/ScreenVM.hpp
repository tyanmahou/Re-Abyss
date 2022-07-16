#pragma once
#include <abyss/views/Shader/Dither/DitherShader.hpp>

namespace abyss::UI::Fade::Screen
{
    class ScreenVM
    {
    public:
        ScreenVM& setFadeTimeSec(double fadeTimeSec)
        {
            m_fadeTimeSec = fadeTimeSec;
            return *this;
        }
        ScreenVM& setIsFadeOut(bool isFadeOut)
        {
            m_isFadeOut = isFadeOut;
            return *this;
        }
        void draw() const;
    private:
        double m_fadeTimeSec = 0;
        bool m_isFadeOut = true;

        DitherShader m_shader;
    };
}
