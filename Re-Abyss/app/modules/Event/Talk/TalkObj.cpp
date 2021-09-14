#include "TalkObj.hpp"
#include <abyss/components/Event/Talk/Common/TalkHandler.hpp>

namespace abyss::Event::Talk
{
    TalkObj::TalkObj(EventObj* pEvent):
        m_pEvent(pEvent)
    {
        m_talk = this->attach<TalkHandler>(this);
    }
    bool TalkObj::update()
    {
        return m_talk->update();
    }
}
