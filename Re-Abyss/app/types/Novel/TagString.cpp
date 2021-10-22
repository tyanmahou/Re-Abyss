#include "TagString.hpp"
#include <abyss/utils/Overloaded.hpp>

namespace abyss::Novel
{
    TagString& TagString::append(const value_type& ch, double time)
    {
        m_str << ch;
        m_times << time;
        return *this;
    }
    Coro::Generator<TagChar>::iterator TagString::begin() const
    {
        s3d::ColorF color{};
        auto tagVisitor = overloaded{
            [&](const Tag::Color& tag) {color = tag.color;}
        };

        size_t tagIndex = 0;
        size_t tagCount = m_tags.size();
        for (size_t index = 0; index < m_str.length(); ++index) {
            for (; tagIndex < tagCount; ++tagIndex) {
                if (m_tags[tagIndex].first > index) {
                    break;
                }
                std::visit(tagVisitor, m_tags[tagIndex].second);
            }
            co_yield TagChar{
                .ch = m_str[index],
                .color = color,
                .time = m_times[index],
            };
        }
        co_return;
    }
    Coro::Generator<TagChar>::iterator_end TagString::end() const
    {
        return {};
    }
}