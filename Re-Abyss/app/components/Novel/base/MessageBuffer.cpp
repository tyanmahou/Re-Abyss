#include "MessageBuffer.hpp"

namespace abyss::Novel
{
    MessageBuffer::MessageBuffer(TalkObj* pTalk):
        m_pTalk(pTalk)
    {}
    void MessageBuffer::append(const char32_t ch)
    {
        m_message.append(TagChar{
            .ch = ch,
            .color = m_color
        });
    }
}
