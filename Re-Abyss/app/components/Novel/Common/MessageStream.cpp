#include "MessageStream.hpp"
#include <abyss/utils/Coro/Wait/Wait.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/components/Novel/base/MessageBuffer.hpp>

#include <Siv3D.hpp>

namespace abyss::Novel
{
    MessageStream::MessageStream(TalkObj* pTalk, const s3d::String& message):
        m_pTalk(pTalk),
        m_message(message)
    {}
    void MessageStream::onStart()
    {}
    void MessageStream::onEnd()
    {
        auto buffer = m_pTalk->find<MessageBuffer>();
        for (size_t index = m_done + 1; index < m_message.size(); ++index) {
            buffer->append(m_message[index]);
        }
    }

    Coro::Task<> MessageStream::onCommand()
    {
        auto buffer = m_pTalk->find<MessageBuffer>();
        size_t index = 0;
        for (char32_t ch : m_message) {
            m_done = index;
            buffer->append(ch);
            co_await Coro::WaitForSeconds(0.02s);
            ++index;
        }
        co_return;
    }
}
