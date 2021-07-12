#include "System.hpp"
#include <abyss/system/base/ICoreSystem.hpp>

namespace abyss::Sys
{
    void System::update()
    {
        m_core->update();
    }

    void System::draw() const
    {
        m_core->draw();
    }
}