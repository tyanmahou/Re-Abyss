#include "WaitInput.hpp"
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/components/Novel/base/MessageBuffer.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>

namespace abyss::Novel
{
    WaitInput::WaitInput(TalkObj* pTalk):
        m_pTalk(pTalk)
    {}
    void WaitInput::onStart()
    {
        m_pTalk->find<MessageBuffer>()->setIsInputWait(true);
    }
    void WaitInput::onEnd()
    {
        m_pTalk->find<MessageBuffer>()->setIsInputWait(false);
    }
    Coro::Task<> WaitInput::onCommand()
    {
        while (true) {
            if (InputManager::A.down() || InputManager::B.down()) {
                break;
            }
        }
        co_return;
    }
}
