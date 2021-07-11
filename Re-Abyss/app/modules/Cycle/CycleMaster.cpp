#include "CycleMaster.hpp"

namespace abyss::Cycle
{
    void CycleMaster::setManager(Manager* pManager)
    {
        m_master.setManager(pManager);
    }
    void CycleMaster::init()
    {
        m_master.setup();
        m_master.start();
    }
    void CycleMaster::update()
    {
        m_master.update();
    }
    void CycleMaster::finalize()
    {
        m_master.end();
    }
}
