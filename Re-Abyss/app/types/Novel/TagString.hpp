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
            m_str(str)
        {}
    private:
        s3d::String m_str;
    };
}