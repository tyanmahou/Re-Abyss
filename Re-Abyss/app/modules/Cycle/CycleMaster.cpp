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
    void CycleMaster::finalize()
    {
        m_master.end();
    }
}
