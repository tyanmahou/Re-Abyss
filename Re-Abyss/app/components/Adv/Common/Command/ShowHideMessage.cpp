#include <abyss/components/Adv/Common/Command/ShowHideMessage.hpp>

#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Adv/base/Engine.hpp>
#include <abyss/components/Adv/Common/MessageBox.hpp>
#include <abyss/utils/Coro/Fiber/Wait.hpp>

namespace abyss::Adv
{
    ShowHideMessage::ShowHideMessage(AdvObj* pTalk, bool isShow):
        m_pTalk(pTalk),
        m_isShow(isShow)
    {}
    void ShowHideMessage::onStart()
    {
        if (auto messageBox = m_pTalk->find<MessageBox>()) {
            messageBox->setVisible(m_isShow);
        }
    }
    void ShowHideMessage::onEnd()
    {
        if (auto messageBox = m_pTalk->find<MessageBox>()) {
            messageBox->animToTail();
        }
        if (!m_isShow) {
            // 非表示の場合は終わった時点でバッファクリア
            m_pTalk->engine()->clearBuffer();
        }
    }
    Coro::Fiber<> ShowHideMessage::onCommand()
    {
        auto messageBox = m_pTalk->find<MessageBox>();
        co_await Coro::WaitWhile([&] {
            return messageBox && messageBox->isBusyAnim();
        });
    }
}
