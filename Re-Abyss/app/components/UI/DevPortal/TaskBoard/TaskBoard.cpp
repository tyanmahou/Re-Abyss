#include <abyss/components/UI/DevPortal/TaskBoard/TaskBoard.hpp>

#if ABYSS_DEVELOP
#include <abyss/modules/UI/base/UIObj.hpp>

namespace abyss::UI::DevPortal
{
    TaskBoard::TaskBoard(UIObj* pUi):
        m_pUi(pUi),
        m_task(m_pUi->getModule<GitHub>())
    {
    }
    void TaskBoard::onDraw() const
    {
        m_task.draw();
    }
}
#endif
