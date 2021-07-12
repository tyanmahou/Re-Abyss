#include "System.hpp"
#include <abyss/system/base/IBooter.hpp>

namespace abyss::Sys::Splash
{
    System::System()
    {}

    bool System::boot(IBooter* pBooter)
    {
        return pBooter->onBoot(&m_manager);
    }

    void System::update()
    {

    }

    void System::draw() const
    {

    }
}