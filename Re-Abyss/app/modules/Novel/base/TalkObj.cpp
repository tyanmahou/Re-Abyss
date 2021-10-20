#include "TalkObj.hpp"
#include <abyss/components/Novel/base/Engine.hpp>

namespace abyss::Novel
{
    TalkObj::TalkObj()
    {
        m_engine = this->attach<Engine>(this);
    }
    bool TalkObj::update()
    {
        return m_engine->update();
    }
}
