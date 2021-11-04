#include "MessageBox.hpp"
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/UI/UIs.hpp>

#include <abyss/components/UI/Message/Builder.hpp>

namespace abyss::Novel
{
    MessageBox::MessageBox(TalkObj* pTalk):
        m_pTalk(pTalk)
    {}

    void MessageBox::onStart()
    {
        m_pUi = m_pTalk->getModule<UIs>()->create<UI::Message::Builder>(m_pTalk->engine());
        m_msgMain = m_pUi->find<UI::Message::Main>();
        if (m_msgMain) {
            m_msgMain->setVisible(m_isVisible);
        }
    }
    void MessageBox::setVisible(bool isVisible)
    {
        if (m_isVisible == isVisible) {
            return;
        }
        m_isVisible = isVisible;
        if (m_msgMain) {
            m_msgMain->setVisible(m_isVisible);
        }
    }
    bool MessageBox::isBusyAnim() const
    {
        if (m_msgMain) {
            return m_msgMain->isBusyAnim();
        }
        return false;
    }
}
