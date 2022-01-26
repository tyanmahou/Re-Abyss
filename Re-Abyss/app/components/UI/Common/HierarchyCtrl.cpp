#include <abyss/components/UI/Common/HierarchyCtrl.hpp>

namespace abyss::UI
{
    HierarchyCtrl::HierarchyCtrl(UIObj* pUi):
        m_pUi(pUi)
    {}
    void HierarchyCtrl::setup(Executer executer)
    {
        if (m_setupCallback) {
            m_setupCallback(executer);
        }
    }
    void HierarchyCtrl::onStart()
    {
        m_manager.hierarchyUpdate();
    }
    void HierarchyCtrl::onPostUpdate()
    {
        m_manager.update();
    }
    void HierarchyCtrl::onDraw() const
    {
        m_manager.draw();
    }
    void HierarchyCtrl::push(const HierarchyManager::Hierarchy_t& next)
    {
        m_manager.push(next);
    }
}
