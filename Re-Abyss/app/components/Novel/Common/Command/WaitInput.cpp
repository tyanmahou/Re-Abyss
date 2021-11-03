#include "WaitInput.hpp"
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/components/Novel/base/Engine.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>

namespace abyss::Novel
{
    WaitInput::WaitInput(TalkObj* pTalk):
        m_pTalk(pTalk)
    {}
    void WaitInput::onStart()
    {
        m_pTalk->engine()->setIsInputWait(true);
    }
    void WaitInput::onEnd()
    {
        m_pTalk->engine()->setIsInputWait(false);
    }
    Coro::Task<> WaitInput::onCommand()
    {
        // 1フレーム待つ
        co_yield{};
        while (true) {
            if (InputManager::A.down() || InputManager::B.down()) {
                break;
            }
            co_yield{};
        }
        // 1フレーム待つ
        co_yield{};
        co_return;
    }
}
