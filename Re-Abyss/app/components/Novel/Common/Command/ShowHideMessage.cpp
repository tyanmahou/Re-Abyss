#include "ShowHideMessage.hpp"
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/components/Novel/base/Engine.hpp>
#include <abyss/components/Novel/Common/MessageBox.hpp>
#include <abyss/utils/Coro/Wait/Wait.hpp>

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
        if (!m_isShow) {
            // 非表示の場合は終わった時点でバッファクリア
            m_pTalk->engine()->clearBuffer();
        }
    }
    Coro::Task<> ShowHideMessage::onCommand()
    {
        auto messageBox = m_pTalk->find<MessageBox>();
        co_await Coro::WaitWhile([&] {
            return messageBox && messageBox->isBusyAnim();
        });
    }
}
