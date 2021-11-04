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
    }
}
