#pragma once
#include <Siv3D/String.hpp>
#include <Siv3D/ColorF.hpp>

namespace abyss::Novel
{
    struct TagChar
    {
        char32_t ch;
        s3d::ColorF color;
    };
    /// <summary>
    /// タグ付き文字列
    /// </summary>
    class TagString
    {
    public:
        using string_type = s3d::Array<TagChar>;
        using value_type = string_type::value_type;
        using const_iterator = string_type::const_iterator;
    public:
        TagString() = default;
    public:
        TagString& append(const value_type& s)
        {
            m_str << s;
            return *this;
        }
        size_t length() const
        {
            return size();
        }
        size_t size() const
        {
            return m_str.size();
        }
        const_iterator begin() const
        {
            return m_str.begin();
        }
        const_iterator end() const
        {
            return m_str.end();
        }
    private:
        string_type m_str;
    };
}