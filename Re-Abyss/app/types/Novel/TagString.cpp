#include <abyss/types/Novel/TagString.hpp>
#include <abyss/utils/Overloaded.hpp>

namespace abyss::Novel
{
    TagString& TagString::append(const value_type& ch, double time)
    {
        m_str << ch;
        m_times << time;
        return *this;
    }
    void TagString::clear()
    {
        m_str.clear();
        m_times.clear();
        m_tags.clear();
    }
    Coro::Iterator<TagChar> TagString::begin() const
    {
        s3d::ColorF color{};
        bool isShake = false;
        auto tagVisitor = overloaded{
            [&](const Tag::Color& tag) {color = tag.color;},
            [&](const Tag::Shake& tag) {isShake = tag.isShake; },
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
                .isShake = isShake,
                .time = m_times[index],
            };
        }
        co_return;
    }
    Coro::IteratorEnd TagString::end() const
    {
        return {};
    }
}