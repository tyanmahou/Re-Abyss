#pragma once
#include <Siv3D/Texture.hpp>

namespace abyss::FieldEnv
{
    class CausticsView
    {
        s3d::Texture m_texture;
        double m_time;
    public:
        CausticsView();

        CausticsView& setTime(double time);

        void drawBack(const s3d::Vec2& pos) const;
        void drawFront(const s3d::Vec2& pos) const;
    };
}
