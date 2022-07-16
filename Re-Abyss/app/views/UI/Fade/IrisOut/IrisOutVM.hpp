#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/ColorF.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::UI::Fade::IrisOut
{
    class IrisOutVM
    {
    public:
        IrisOutVM& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }
        IrisOutVM& setFadeTimeSec(double fadeTimeSec)
        {
            m_fadeTimeSec = fadeTimeSec;
            return *this;
        }
        IrisOutVM& setIsFadeOut(bool isFadeOut)
        {
            m_isFadeOut = isFadeOut;
            return *this;
        }
        IrisOutVM& setColor(const s3d::ColorF& color)
        {
            m_color = color;
            return *this;
        }
        void draw() const;
    private:
        s3d::Vec2 m_pos;
        double m_fadeTimeSec = 0;
        bool m_isFadeOut = true;
        s3d::Optional<s3d::ColorF> m_color;
    };
}
