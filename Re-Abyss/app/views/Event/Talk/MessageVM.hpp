#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/StringView.hpp>

namespace abyss::Event::Talk
{
    class MessageVM
    {
        s3d::Vec2 m_pos;
        s3d::String m_currentMessage;
        s3d::String m_prevMessage;
        s3d::int32 m_strIndex = 0;
    public:
        MessageVM& setPos(const s3d::Vec2& pos);
        MessageVM& setCurrent(const s3d::String& current);
        MessageVM& setPrev(const s3d::String& prev);
        MessageVM& setStrIndex(s3d::int32 strIndex);
        void draw() const;
    };
}