#pragma once
#include <Siv3D/Vector2D.hpp>

namespace abyss::ui::Fade
{
    class IrisOutVM
    {
        s3d::Vec2 m_pos;
        double m_fadeTimeSec = 0;
        bool m_isFadeOut = true;
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
        void draw() const;
    };
}