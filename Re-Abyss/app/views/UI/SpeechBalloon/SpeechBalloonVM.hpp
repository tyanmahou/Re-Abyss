#pragma once
#include <Siv3D/Texture.hpp>

namespace abyss::UI::SpeechBalloon
{
    class SpeechBalloonVM
    {
    public:
        SpeechBalloonVM();

        SpeechBalloonVM& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }
        SpeechBalloonVM& setTime(double time)
        {
            m_time = time;
            return *this;
        }
        void draw() const;
    private:
        s3d::Texture m_texture;
        s3d::Vec2 m_pos;
        double m_time = 0;
    };
}