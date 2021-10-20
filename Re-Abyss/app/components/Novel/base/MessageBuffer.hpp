#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/types/Novel/TagString.hpp>

namespace abyss::Novel
{
    class MessageBuffer : public IComponent
    {
    public:
        MessageBuffer(TalkObj* pTalk);

        void append(const char32_t ch);

        MessageBuffer& setColor(const s3d::ColorF& color)
        {
            m_color = color;
            return *this;
        }
        const TagString& getMessage() const
        {
            return m_message;
        }
    private:
        TalkObj* m_pTalk;

        TagString m_message;

        s3d::ColorF m_color;
    };
}