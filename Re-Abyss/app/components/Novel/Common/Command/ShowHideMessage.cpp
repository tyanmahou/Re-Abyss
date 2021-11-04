#include "ShowHideMessage.hpp"
#include <abyss/modules/Novel/base/TalkObj.hpp>
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
    Coro::Task<> ShowHideMessage::onCommand()
    {
        auto messageBox = m_pTalk->find<MessageBox>();
        co_await Coro::WaitWhile([&] {
            return messageBox && messageBox->isBusyAnim();
        });
    }
}
