#include <abyss/components/Adv/Common/MessageBox.hpp>

#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/UI/UIs.hpp>

#include <abyss/components/UI/Message/Builder.hpp>

namespace abyss::Adv
{
    MessageBox::MessageBox(AdvObj* pObj):
        m_pObj(pObj)
    {}

    void MessageBox::onStart()
    {
        m_pUi = m_pObj->getModule<UIs>()->create<UI::Message::Builder>(m_pObj->sentence());
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
    void MessageBox::animToTail() const
    {
        if (m_msgMain) {
            m_msgMain->animToTail();
        }
    }
}
