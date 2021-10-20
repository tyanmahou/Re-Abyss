#pragma once
#include <Siv3D/String.hpp>

namespace abyss::Novel
{
    /// <summary>
    /// タグ付き文字列
    /// </summary>
    class TagString
    {
    public:
        TagString() = default;
        TagString(const s3d::String& str) :
            m_message(str)
        {}
    public:
        size_t length() const
        {
            return m_message.length();
        }
    private:
        s3d::String m_message;
    };
}