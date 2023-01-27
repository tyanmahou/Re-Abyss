#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/Novel/base/Engine.hpp>

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
