#pragma once
#include <variant>
#include <concepts>
#include <Siv3D/String.hpp>
#include <Siv3D/ColorF.hpp>
#include <abyss/utils/Coro/Iterator/Iterator.hpp>

namespace abyss::Novel
{

    namespace Tag
    {
        struct Color
        {
            s3d::ColorF color;
        };
    };
    using TagValue = std::variant<
        Tag::Color
    >;
    template<class T>
    concept TagType = std::constructible_from<TagValue, T>;

    struct TagChar
    {
        char32_t ch;
        s3d::ColorF color;
        double time;
    };
    /// <summary>
    /// タグ付き文字列
    /// </summary>
    class TagString
    {
    public:
        using string_type = s3d::String;
        using value_type = string_type::value_type;
    public:
    public:
        TagString() = default;
    public:
        TagString& append(const value_type& ch, double time = 0);


        template<TagType T>
        TagString& append(const T& tag)
        {
            m_tags.emplace_back(m_str.size(), tag);
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


        Coro::Iterator<TagChar> begin() const;
        Coro::IteratorEnd end() const;

    private:
        s3d::String m_str;
        s3d::Array<double> m_times;
        s3d::Array<std::pair<size_t, TagValue>> m_tags;
    };
}