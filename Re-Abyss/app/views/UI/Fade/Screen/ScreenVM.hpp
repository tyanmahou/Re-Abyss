#pragma once
#include <abyss/views/Shader/Dither/DitherShader.hpp>
#include <Siv3D/ColorF.hpp>
#include <Siv3D/Optional.hpp>

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
        ScreenVM& setColor(const s3d::ColorF& color)
        {
            m_color = color;
            return *this;
        }
        void draw() const;
    private:
        double m_fadeTimeSec = 0;
        bool m_isFadeOut = true;
        s3d::Optional<s3d::ColorF> m_color;

        DitherShader m_shader;
    };
}
