#include <abyss/components/Adv/Common/Command/WaitInput.hpp>
#include <abyss/commons/InputManager/InputManager.hpp>
#include <abyss/modules/Adv/base/SentenceCtrl.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>

namespace abyss::Adv
{
    WaitInput::WaitInput(AdvObj* pObj):
        m_pObj(pObj)
    {}
    void WaitInput::onStart()
    {
        m_pObj->sentence()->setIsInputWait(true);
    }
    void WaitInput::onEnd()
    {
        m_pObj->sentence()->setIsInputWait(false);
    }
    Coro::Fiber<> WaitInput::onCommand()
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
