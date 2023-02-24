#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Adv/base/Engine.hpp>

namespace abyss::Adv
{
    AdvObj::AdvObj()
    {
        m_engine = this->attach<Engine>(this);
    }
    bool AdvObj::update()
    {
        return m_engine->update();
    }
}
