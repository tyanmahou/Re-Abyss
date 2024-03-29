#include <abyss/components/Adv/Common/Command/ShowHideMessage.hpp>

#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Adv/base/SentenceCtrl.hpp>
#include <abyss/components/Adv/Common/MessageBox.hpp>
#include <abyss/utils/Coro/Fiber/FiberUtil.hpp>

namespace abyss::Adv
{
    ShowHideMessage::ShowHideMessage(AdvObj* pObj, bool isShow):
        m_pObj(pObj),
        m_isShow(isShow)
    {}
    void ShowHideMessage::onStart()
    {
        if (auto messageBox = m_pObj->find<MessageBox>()) {
            messageBox->setVisible(m_isShow);
        }
    }
    void ShowHideMessage::onEnd()
    {
        if (auto messageBox = m_pObj->find<MessageBox>()) {
            messageBox->animToTail();
        }
        if (!m_isShow) {
            // 非表示の場合は終わった時点でバッファクリア
            m_pObj->sentence()->clearBuffer();
        }
    }
    Coro::Fiber<> ShowHideMessage::onCommand()
    {
        auto messageBox = m_pObj->find<MessageBox>();
        co_await Coro::FiberUtil::WaitWhile([&] {
            return messageBox && messageBox->isBusyAnim();
        });
    }
}
