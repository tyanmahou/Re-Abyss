#include "TalkObj.hpp"
#include <abyss/components/Novel/base/TalkHandler.hpp>
#include <abyss/components/Novel/base/MessageBuffer.hpp>

namespace abyss::Novel
{
    TalkObj::TalkObj()
    {
        this->attach<MessageBuffer>(this);
        m_talk = this->attach<TalkHandler>(this);
    }
    bool TalkObj::update()
    {
        return m_talk->update();
    }
}
