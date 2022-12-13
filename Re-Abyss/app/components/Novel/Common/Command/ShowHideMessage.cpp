#include <abyss/components/Novel/Common/Command/ShowHideMessage.hpp>

#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/components/Novel/base/Engine.hpp>
#include <abyss/components/Novel/Common/MessageBox.hpp>
#include <abyss/utils/Coro/Fiber/Wait.hpp>

namespace abyss::Novel
{
    ShowHideMessage::ShowHideMessage(TalkObj* pTalk, bool isShow):
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
