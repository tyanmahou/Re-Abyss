#include "TalkObj.hpp"
#include <abyss/components/Novel/base/TalkHandler.hpp>

namespace abyss::Novel
{
    TalkObj::TalkObj()
    {
        m_talk = this->attach<TalkHandler>(this);
    }
    bool TalkObj::update()
    {
        return m_talk->update();
    }
}
