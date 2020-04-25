#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/StringView.hpp>

namespace abyss::Event::Talk
{
    class MessageVM
    {
        s3d::Vec2 m_pos;
        s3d::StringView m_currentMessage;
        s3d::StringView m_prevMessage;
        s3d::int32 m_strIndex = 0;
    public:
        MessageVM& setPos(const s3d::Vec2& pos);
        MessageVM& setCurrent(s3d::StringView current);
        MessageVM& setPrev(s3d::StringView prev);
        MessageVM& setStrIndex(s3d::int32 strIndex);
        void draw() const;
    };
}