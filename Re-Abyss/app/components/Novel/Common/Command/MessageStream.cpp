#include <abyss/components/Novel/Common/Command/MessageStream.hpp>
#include <abyss/utils/Coro/Task/Wait.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/components/Novel/base/Engine.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
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
        const auto& engine = m_pTalk->engine();
        for (size_t index = m_done + 1; index < m_message.size(); ++index) {
            engine->append(m_message[index]);
        }
    }

    Coro::Task<> MessageStream::onCommand()
    {
        return skip() | stream();
    }
    Coro::Task<> MessageStream::stream()
    {
        const auto& engine = m_pTalk->engine();
        auto* globalTime = m_pTalk->getModule<GlobalTime>();
        size_t index = 0;
        for (char32_t ch : m_message) {
            m_done = index;
            engine->append(ch);
            co_await Coro::WaitForSeconds(60ms, globalTime);
            ++index;
        }
        co_return;
    }
    Coro::Task<> MessageStream::skip()
    {
        while (true) {
            if (InputManager::A.down()) {
                co_return;
            }
            co_yield{};
        }
    }
}
