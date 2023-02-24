#include <abyss/components/Adv/Common/Command/MessageStream.hpp>
#include <abyss/utils/Coro/Fiber/Wait.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Adv/base/Engine.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
#include <Siv3D.hpp>

namespace abyss::Adv
{
    MessageStream::MessageStream(AdvObj* pTalk, const s3d::String& message):
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

    Coro::Fiber<> MessageStream::onCommand()
    {
        return skip() | stream();
    }
    Coro::Fiber<> MessageStream::stream()
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
    Coro::Fiber<> MessageStream::skip()
    {
        while (true) {
            if (InputManager::A.down()) {
                co_return;
            }
            co_yield{};
        }
    }
}
