#include "SelectFrameCtrl.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>

namespace abyss::UI::SaveSelect::Main
{
    SelectFrameCtrl::SelectFrameCtrl(UIObj* pUi):
        m_pUi(pUi),
        m_view(std::make_unique<SelectFrame::SelectFrameVM>())
    {}

    void SelectFrameCtrl::onStart()
    {
        m_users = m_pUi->find<Main::Users>();
    }

    void SelectFrameCtrl::onDraw() const
    {
        m_view
            ->setSelectUserId(m_users->getSelectId())
            .draw();
    }
}
